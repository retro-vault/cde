#!/bin/sh
# Build and test using the maintained toolchain image; install no packages.
set -eu
run_tests=1
case "${1:-}" in
    --build-only) run_tests=0; shift ;;
    "") ;;
    *) echo "Usage: $0 [--build-only]" >&2; exit 2 ;;
esac
[ "$#" -eq 0 ] || { echo "Usage: $0 [--build-only]" >&2; exit 2; }
cd "$(dirname "$0")/.."
exec docker run --rm -i \
    --env CDE_RUN_TESTS="$run_tests" \
    --env CDE_BUILD_UID="$(id -u)" --env CDE_BUILD_GID="$(id -g)" \
    --volume "$PWD:/work" --workdir /work \
    wischner/gcc-x86_64-linux-motif sh -eu -s <<'CONTAINER'
rpcbind
# Desktop programs also resolve their current UID through the account database.
# This account exists only for the lifetime of the disposable container.
if ! getent group "$CDE_BUILD_GID" >/dev/null; then
    groupadd --gid "$CDE_BUILD_GID" cde-build
fi
if ! getent passwd "$CDE_BUILD_UID" >/dev/null; then
    useradd --no-create-home --uid "$CDE_BUILD_UID" --gid "$CDE_BUILD_GID" \
        --home-dir /work/build/account-home --shell /bin/ksh cde-build
fi
setpriv --reuid "$CDE_BUILD_UID" --regid "$CDE_BUILD_GID" --clear-groups \
    sh -eu -c '
        mkdir -p build/tmp build/account-home
        export TMPDIR=/work/build/tmp
        cmake -S . -B build/linux -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
        cmake --build build/linux --parallel 8
        cmake --install build/linux
    '
[ "$CDE_RUN_TESTS" -eq 1 ] || exit 0
exec tests/run-services.sh "$CDE_BUILD_UID" "$CDE_BUILD_GID" /work/build/linux
CONTAINER

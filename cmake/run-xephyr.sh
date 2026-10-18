#!/bin/sh
# Run the staged desktop and its nested X server in the toolchain container.
set -eu
cd "$(dirname "$0")/.."
case "${1:-}" in
    ""|--smoke-test) ;;
    *) echo "Usage: $0 [--smoke-test]" >&2; exit 2 ;;
esac
[ "$#" -le 1 ] || exit 2
command -v docker >/dev/null || { echo "Docker is required." >&2; exit 1; }
# Only the parent socket is shared; Xephyr creates its own socket in the container.
case "${DISPLAY:-}" in
    :*|unix:*) parent_number=${DISPLAY#*:}; parent_number=${parent_number%%.*} ;;
    *) echo "Run from a local X11/Xwayland desktop with DISPLAY set." >&2; exit 1 ;;
esac
case "$parent_number" in
    ""|*[!0-9]*) echo "Unsupported local DISPLAY: $DISPLAY" >&2; exit 1 ;;
esac
parent_socket=/tmp/.X11-unix/X$parent_number
parent_authority=${XAUTHORITY:-$HOME/.Xauthority}
[ -S "$parent_socket" ] || { echo "Parent X socket is missing: $parent_socket" >&2; exit 1; }
[ -r "$parent_authority" ] || { echo "Cannot read X authority: $parent_authority" >&2; exit 1; }
[ -x bin/bin/Xsession ] || { echo "Build first: ./cmake/docker-build.sh --build-only" >&2; exit 1; }
mkdir -p build/xephyr
printf 'Starting CDE in Xephyr. Session files and logs: %s/build/xephyr\n' "$PWD"
exec docker run --rm --init \
    --hostname cde-xephyr \
    --env CDE_BUILD_UID="$(id -u)" --env CDE_BUILD_GID="$(id -g)" \
    --env CDE_PARENT_DISPLAY=":$parent_number" \
    --env CDE_XEPHYR_SCREEN="${CDE_XEPHYR_SCREEN:-1280x800}" \
    --volume "$PWD:/work" --workdir /work \
    --mount "type=bind,src=$parent_socket,dst=$parent_socket,readonly" \
    --mount "type=bind,src=$parent_authority,dst=/run/cde-parent.Xauthority,readonly" \
    wischner/gcc-x86_64-linux-motif \
    /usr/bin/flock --nonblock --no-fork /work/build/xephyr/session.lock \
    /bin/bash /work/cmake/xephyr-session.sh "${1:-}"

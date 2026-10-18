#!/bin/sh
# Run the system RPC services only inside the disposable build container.
set -eu
build_uid=$1
build_gid=$2
build_dir=$3
shift 3
service_dir=$build_dir/tests/services
# Each invocation uses a fresh calendar store; ownership remains that of the
# service until the complete test invocation has finished.
rm -rf "$service_dir/calendar" "$service_dir/tooltalk"
mkdir -p "$service_dir/calendar" "$service_dir/tooltalk" "$service_dir/pam"
build_user=$(getent passwd "$build_uid" | cut -d: -f1)
printf 'auth required %s/tests/pam/cde-pam-fixture.so %s\naccount required pam_permit.so\nsession required pam_permit.so\n' \
    "$build_dir" "$build_user" > "$service_dir/pam/cde-port-test"
ln -s "$service_dir/pam/cde-port-test" /etc/pam.d/cde-port-test
printf 'auth required %s/tests/pam/cde-pam-fixture.so %s\naccount required pam_deny.so\n' \
    "$build_dir" "$build_user" > "$service_dir/pam/cde-port-test-denied"
ln -s "$service_dir/pam/cde-port-test-denied" /etc/pam.d/cde-port-test-denied
printf '/ %s\n/work %s\n' "$service_dir/tooltalk" "$service_dir/tooltalk" > "$service_dir/partition-map"
calendar_pid=
tooltalk_pid=
cleanup() {
    trap - EXIT HUP INT TERM
    [ -z "$calendar_pid" ] || kill "$calendar_pid" 2>/dev/null || :
    [ -z "$tooltalk_pid" ] || kill "$tooltalk_pid" 2>/dev/null || :
    wait 2>/dev/null || :
    rm -f /etc/pam.d/cde-port-test /etc/pam.d/cde-port-test-denied
    chown -R "$build_uid:$build_gid" "$service_dir"
}
trap cleanup EXIT HUP INT TERM
"$build_dir/src/rpc.cmsd/rpc.cmsd" -s -D "$service_dir/calendar" > "$service_dir/calendar.log" 2>&1 &
calendar_pid=$!
TT_PARTITION_MAP="$service_dir/partition-map" \
    "$build_dir/src/rpc.ttdbserver/rpc.ttdbserver" -S > "$service_dir/tooltalk.log" 2>&1 &
tooltalk_pid=$!
setpriv --reuid "$build_uid" --regid "$build_gid" --clear-groups \
    ctest --test-dir "$build_dir" --output-on-failure "$@"

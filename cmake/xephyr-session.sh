#!/bin/bash
# Container entry point. Root is used only for the isolated RPC services.
set -eu
umask 077
runtime=/work/build/xephyr
export HOME=$runtime/home TMPDIR=$runtime/tmp
export XAUTHORITY=$HOME/.Xauthority LANG=C.UTF-8 SHELL=/bin/ksh
export PATH=/work/bin/bin:$PATH
export MAIL=$HOME/Mail/Inbox
mkdir -p "$HOME/Mail" "$TMPDIR" "$runtime/logs" "$runtime/calendar" "$runtime/tooltalk"
touch "$MAIL"
chmod 600 "$MAIL"
chmod 1777 /tmp/.X11-unix
if ! getent group "$CDE_BUILD_GID" >/dev/null; then
    groupadd --gid "$CDE_BUILD_GID" cde-build
fi
if ! getent passwd "$CDE_BUILD_UID" >/dev/null; then
    useradd --no-create-home --uid "$CDE_BUILD_UID" --gid "$CDE_BUILD_GID" \
        --home-dir "$HOME" --shell /bin/ksh cde-build
fi
USER=$(getent passwd "$CDE_BUILD_UID" | cut -d: -f1)
export USER LOGNAME=$USER
parent_auth=$runtime/parent.Xauthority
rm -f "$parent_auth"
touch "$parent_auth" "$XAUTHORITY"
chmod 600 "$parent_auth" "$XAUTHORITY"
# FamilyWild entries allow the host cookie to work with the container hostname.
source_auth=$runtime/source.Xauthority
cp /run/cde-parent.Xauthority "$source_auth"
chmod 600 "$source_auth"
xauth -f "$source_auth" nlist | sed 's/^..../ffff/' | xauth -f "$parent_auth" nmerge -
rm -f "$source_auth"
DISPLAY=:1
[ "$CDE_PARENT_DISPLAY" != "$DISPLAY" ] || DISPLAY=:2
export DISPLAY
cookie=$(od -An -N16 -tx1 /dev/urandom | tr -d ' \n')
xauth -f "$XAUTHORITY" add "$DISPLAY" MIT-MAGIC-COOKIE-1 "$cookie"
unset cookie
chown -R "$CDE_BUILD_UID:$CDE_BUILD_GID" "$HOME" "$TMPDIR" "$runtime/logs"
chown "$CDE_BUILD_UID:$CDE_BUILD_GID" "$parent_auth"
# Calendar files belong to its service while running, and to the developer after exit.
chown -R root:root "$runtime/calendar"
printf '/ %s\n/work %s\n' "$runtime/tooltalk" "$runtime/tooltalk" > "$runtime/partition-map"
xephyr_pid= calendar_pid= tooltalk_pid= session_pid= resize_pid=
cleanup() {
    trap - EXIT HUP INT TERM
    if [ -n "$session_pid" ]; then
        kill -TERM -- "-$session_pid" 2>/dev/null || :
    fi
    for child in "$session_pid" "$xephyr_pid" "$calendar_pid" "$tooltalk_pid" "$resize_pid"; do
        [ -z "$child" ] || kill "$child" 2>/dev/null || :
    done
    # A client can remain blocked after its X server disappears. Bound shutdown
    # rather than waiting indefinitely for every desktop process to cooperate.
    for ((attempt = 0; attempt < 30; ++attempt)); do
        alive=0
        for child in "$session_pid" "$xephyr_pid" "$calendar_pid" "$tooltalk_pid" "$resize_pid"; do
            if [ -n "$child" ] && kill -0 "$child" 2>/dev/null; then
                alive=1
            fi
        done
        [ "$alive" -eq 1 ] || break
        sleep 0.1
    done
    if [ -n "$session_pid" ]; then
        kill -KILL -- "-$session_pid" 2>/dev/null || :
    fi
    for child in "$session_pid" "$xephyr_pid" "$calendar_pid" "$tooltalk_pid" "$resize_pid"; do
        [ -z "$child" ] || kill -KILL "$child" 2>/dev/null || :
    done
    wait 2>/dev/null || :
    chown -R "$CDE_BUILD_UID:$CDE_BUILD_GID" "$runtime/calendar" "$runtime/tooltalk" "$runtime/logs"
    chown "$CDE_BUILD_UID:$CDE_BUILD_GID" "$runtime/partition-map"
    rm -f "$parent_auth"
}
trap cleanup EXIT
trap 'exit 130' HUP INT TERM
user_command=(setpriv --reuid "$CDE_BUILD_UID" --regid "$CDE_BUILD_GID" --clear-groups)
rpcbind
/work/bin/libexec/cde/rpc.cmsd -s -D "$runtime/calendar" > "$runtime/logs/calendar.log" 2>&1 &
calendar_pid=$!
TT_PARTITION_MAP="$runtime/partition-map" \
    /work/bin/libexec/cde/rpc.ttdbserver -S > "$runtime/logs/tooltalk.log" 2>&1 &
tooltalk_pid=$!
"${user_command[@]}" env DISPLAY="$CDE_PARENT_DISPLAY" XAUTHORITY="$parent_auth" \
    Xephyr "$DISPLAY" -screen "$CDE_XEPHYR_SCREEN" -resizeable -noreset -nolisten tcp \
    -auth "$XAUTHORITY" -title 'CDE - Xephyr' > "$runtime/logs/xephyr.log" 2>&1 &
xephyr_pid=$!
attempt=0
until "${user_command[@]}" xdpyinfo >/dev/null 2>&1; do
    attempt=$((attempt + 1))
    if [ "$attempt" -ge 100 ] || ! kill -0 "$xephyr_pid" 2>/dev/null; then
        cat "$runtime/logs/xephyr.log" >&2
        echo "Xephyr could not start." >&2
        exit 1
    fi
    sleep 0.1
done
"${user_command[@]}" /work/bin/libexec/cde/xephyr-resize > "$runtime/logs/resize.log" 2>&1 &
resize_pid=$!
if [ "${1:-}" = --smoke-test ]; then
    "${user_command[@]}" timeout 35 /work/build/linux/tests/wm/test_wm_manage /work/bin/bin/Xsession xsession
else
    setsid "${user_command[@]}" /work/bin/bin/Xsession &
    session_pid=$!
    # Either Exit in CDE or closing Xephyr ends this launch.
    status=0
    wait -n "$session_pid" "$xephyr_pid" "$resize_pid" || status=$?
    if ! kill -0 "$xephyr_pid" 2>/dev/null; then
        status=0
    fi
    exit "$status"
fi

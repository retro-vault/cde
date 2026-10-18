# CDE for x86-64 Linux

CDE 2.5.3 with a native, nested CMake build for x86-64 Linux, C11 and C++11.
The source tree is self-contained. The reference source at
../cdesktopenv-code is not used during builds.
Baseline upstream commit: c5727a7798af9a3424f090428120132e73315a60.

## Build, stage, and test

```sh
./cmake/docker-build.sh
```

The helper uses wischner/gcc-x86_64-linux-motif and installs no packages.
It starts rpcbind in the disposable container, builds and stages with your
UID/GID, and runs CTest. The image supplies GCC, CMake, Make, Motif, X11,
PAM, libtirpc, LMDB, JPEG, bison, flex, ksh, Tcl, onsgmls, compress and Xvfb.
An ephemeral account lets desktop applications resolve the build UID.
Calendar, ToolTalk and PAM fixtures exist only inside that container.
CMake installs runtime helpers, executable scripts, ToolTalk registrations,
localized help-family files and documentation. CTest also installs into a fresh
DESTDIR under build/ to check the manifest, executable permissions and required
runtime files independently of the existing bin/ tree.

All intermediate files, generated headers/resources, logs and test files
belong under build/. The default build directory is build/linux. Final files
are staged under bin/, including bin/bin, bin/lib, bin/libexec/cde,
bin/include and bin/share/dt. Libraries live under lib/<component>, programs
under src/<component>, public headers under include/<namespace>, and tests
under tests/<component>. Private headers stay with their owning libraries.

Runtime paths default to the configured installation prefix (/work/bin in
this container). CDE_DATA_TOP, CDE_CONFIGURATION_TOP, CDE_LOGFILES_TOP,
CDE_CALENDAR_DIR and CDE_LIBEXEC_DIR are CMake cache paths for packaging.
Installed libraries and executables use relative RUNPATHs for CDE libraries.
The staged tree is an installation prefix; running the build does not
configure the host display manager or install host services.

## Components

The build includes the CDE core libraries, ToolTalk client and servers,
window and session managers, PAM login manager and greeters, file manager,
editor, terminal, mail, calendar client and server, calculator, style and
icon editors, action editor, print manager, embedded Desktop KornShell,
Application Builder and code generator, Information Manager, help tools,
search tools, integration scripts and desktop resources.

Help and searchable information libraries are built from SGML for English,
German, Spanish, French, Italian and Japanese. The English reference manual
is rendered from its sources. Supplied application resources and message
catalogs are built for ten additional locales, using English fallback text
where a resource translation is incomplete. Translation coverage varies
according to the supplied upstream files. A C.UTF-8 tool locale supports
minimal images without separately generated regional locales.

CTest checks live ToolTalk messaging and persistent metadata; database binary
encodings, deletion and reopen behavior; real calendar RPC operations; PAM
conversations and identity reuse; Motif and editor behavior; window framing;
full Xsession startup; desktop application windows; generated help; document
libraries in all six languages; and installed resource expansion. GUI tests
run under Xvfb with isolated homes and files under build/.

These checks are a reproducible build and functional baseline, not exhaustive
application acceptance testing. Calendar data still has historical 2037/2038
limits. Imported source retains compiler warnings and legacy temporary-file
APIs; warnings have not been globally hidden. Solaris-only administration
and discontinued font utilities outside the upstream Linux build are not
part of this Linux desktop.

See [the C coding standard](docs/standards/CSTANDARD.md). Migrated files retain
upstream notices; see COPYING and individual source licenses.

## Run in Xephyr with F5

Open this folder in VS Code, select **CDE desktop in Xephyr** in Run and Debug,
then press **F5**. The pre-launch task builds and stages CDE in the Motif Docker
image; the launcher opens the desktop in a resizable 1280×800 Xephyr window.
This uses VS Code's built-in JavaScript Debug Terminal to run the launcher;
it does not attach a C/C++ debugger. The F5 command replaces its launch shell,
so closing Xephyr also ends the launch terminal and debug session.

Docker must be accessible from VS Code, and VS Code must inherit DISPLAY and
XAUTHORITY from your local X11 or Xwayland desktop. Xephyr runs inside the
image, so no host Xephyr installation or xhost access change is needed.
Only the parent X socket and its authority file are mounted for display access.
The desktop runs as your UID with a separate home and logs under build/xephyr/.
Use CDE's Exit control, close the Xephyr window, or stop the launch terminal
to end the disposable container. The separate home persists between runs. Mailer uses the private local inbox at
build/xephyr/home/Mail/Inbox; the launcher exports MAIL to select it. Clicking
the panel clock opens Digital Clock.

To launch an already staged build from a terminal:

```sh
./cmake/run-xephyr.sh
```

Set CDE_XEPHYR_SCREEN (for example, 1600x1000) to choose the initial window size.

CDE now follows X RandR resolution changes while running. The front panel,
maximized/fullscreen windows, workspace backdrops and desktop-icon grids update without
restarting the session. Inactive workspaces are updated too. Separate RandR
virtual monitor regions retain their own maximize boundaries. The Xephyr launcher
also synchronizes its RandR output mode after resizing so the mouse can reach
the entire desktop. Resize tests check pointer movement and application button
press/release delivery through the parent X server, alongside workspace and
virtual-monitor geometry. They also keep Calendar open during rapid resize
bursts and inject stale RandR replies to verify that the resize helper retries
without terminating the session.

In a virtual machine, this responds when the guest X server reports a new
resolution. Automatic resizing from the VM window still depends on the
hypervisor's guest display integration.

# CDE for x86-64 Linux

The Common Desktop Environment (CDE) 2.5.3 for 64-bit x86 Linux, built with
CMake. It includes the desktop and window manager, login and session tools,
file manager, terminal, editor, mail, calendar, desktop utilities, Application
Builder, Information Manager, and online help.

## Build

You need Docker and access to the `wischner/gcc-x86_64-linux-motif` image.
Run commands from the repository root.

```sh
./cmake/docker-build.sh
```

This compiles CDE, installs it into `bin/`, and runs the test suite inside the
container. The image provides the build dependencies; the script installs no
packages on your host.

To compile and install without running tests:

```sh
./cmake/docker-build.sh --build-only
```

Build files and logs are stored under `build/`. The default build directory is
`build/linux/`, and its `install_manifest.txt` lists the installed files.

## Run in Xephyr

Xephyr runs CDE inside a window on your existing X11 or Xwayland desktop.
Your terminal must have valid `DISPLAY` and `XAUTHORITY` settings.

After building:

```sh
./cmake/run-xephyr.sh
```

In VS Code, select **CDE desktop in Xephyr** under Run and Debug and press
**F5**. This builds and installs CDE before launching it. Close Xephyr or use
CDE's Exit control to end the session.

The default window size is 1280×800. To choose another starting size:

```sh
CDE_XEPHYR_SCREEN=1600x1000 ./cmake/run-xephyr.sh
```

The desktop follows resolution changes and supports multiple workspaces and
virtual monitors. Session settings and files persist in `build/xephyr/home/`,
logs are in `build/xephyr/logs/`, and the local mail inbox is
`build/xephyr/home/Mail/Inbox`.

## Deploy

Choose the final installation prefix before compiling: runtime paths are
configured into the programs and resources. The default Docker build uses
`/work/bin` for running inside the container. For a host installation, build
separately with the intended target path, for example `/opt/cde`:

```sh
docker run --rm \
    --user "$(id -u):$(id -g)" \
    --volume "$PWD:/work" --workdir /work \
    wischner/gcc-x86_64-linux-motif sh -eu -c '
        cmake -S . -B build/deploy \
            -DCMAKE_BUILD_TYPE=Release \
            -DBUILD_TESTING=OFF \
            -DCMAKE_INSTALL_PREFIX=/opt/cde
        cmake --build build/deploy --parallel 8
        DESTDIR=/work/build/deploy-root cmake --install build/deploy
    '
```

The resulting installation is in `build/deploy-root/opt/cde/`. Copy it to the
same prefix on the target machine:

```sh
sudo mkdir -p /opt/cde
sudo cp -a build/deploy-root/opt/cde/. /opt/cde/
```

The target needs an X server and the runtime libraries used by CDE, including
Motif, X11, PAM, libtirpc, LMDB, JPEG and Tcl, plus `/bin/ksh`.

For desktop login, configure your display manager to launch
`/opt/cde/bin/Xsession`, register the supplied PAM configurations in
`/etc/pam.d/`, and configure services for `rpcbind`, ToolTalk's
`rpc.ttdbserver`, and Calendar's `rpc.cmsd`. These host services and display
manager settings are managed separately from the CMake installation.

## Installed files

Paths below are relative to the installation prefix. In the default build,
that prefix is the repository's `bin/` directory.

| Directory | Contents |
| --- | --- |
| `bin/` | Desktop applications, session tools, commands and executable scripts |
| `lib/` | CDE libraries and Desktop KornShell support |
| `libexec/cde/` | Runtime helpers, ToolTalk and Calendar servers, and document tools |
| `include/` | Public development headers |
| `etc/dt/` | Desktop configuration |
| `etc/pam.d/` | Login and screen-unlock PAM configurations |
| `share/dt/` | Icons, fonts, palettes, backdrops, actions, ToolTalk registrations, translations, help and searchable documentation |
| `share/man/` | Manual pages |
| `share/terminfo/` | Terminal description |
| `share/doc/cde/` | License and copyright information |

Online help and searchable documentation are supplied in English, German,
Spanish, French, Italian and Japanese. Application translations vary by locale.

See [COPYING](COPYING) for licensing and
[the C coding standard](docs/standards/CSTANDARD.md) for contributor conventions.

## Acknowledgements

This repository includes software and documentation from the following projects
and contributors:

- **CDE and The Open Group**, the CDE maintainers and community, and the original
  contributors, including Hewlett-Packard, IBM, Sun Microsystems, Novell,
  Digital Equipment Corporation, Fujitsu and Hitachi. CDE artwork and
  documentation are attributed to **The Open Group**; see [COPYING](COPYING).
- **KornShell 93u+m and the AST libraries**, by AT&T and the ksh contributors,
  including David Korn and Martijn Dekker. Desktop KornShell incorporates this
  code. See the [bundled Eclipse Public License 2.0](lib/ksh93/LICENSE.md).
- **tradcpp**, by The NetBSD Foundation and David A. Holland, used to preprocess
  application resources. See its [copyright and license notice](src/tradcpp/main.c).
- **Raima Corporation**, for database code included in
  [Desktop Search](lib/DtSearch/raima).
- **RSA Data Security, Inc.**, for code derived from the **RSA Data Security,
  Inc. MD5 Message-Digest Algorithm**, included in
  [Mailer](lib/DtMail/Common/md5.C).
- **HaL Computer Systems and LRI**, for Information Manager components and the
  [WWL widget wrappers](lib/DtInfo/wwl), and **MIT and the X Consortium**, for
  X11 code incorporated into the desktop and login tools.

CDE also uses external projects including Motif, X.Org/X11, libtirpc, Linux-PAM,
LMDB, libjpeg and Tcl. Their authors and maintainers are gratefully acknowledged.

Individual source files retain their copyright, attribution and license notices.

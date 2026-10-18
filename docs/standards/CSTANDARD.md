# C coding standard

This port targets x86-64 Linux using the LP64 data model, C11, glibc/POSIX APIs,
and X11. New and rewritten C follows this standard; imported legacy functions
are converted incrementally as their behavior is validated. New code has no operating-system selection branches. Keep upstream
copyright and license notices in migrated files.

Use four spaces, no tabs, braces on the same line for control statements and
on a separate line for function definitions. Always brace control statements.
Keep functions focused; use descriptive snake_case names for new local symbols.
Preserve established exported CDE names and layouts when migrating an API.
Public headers live under include/<namespace>; use include guards and C++
linkage guards. Headers must compile without relying on include order.

Use size_t for object sizes and indexes, ptrdiff_t for pointer differences,
and fixed-width integers for defined binary formats. Never store a pointer in
int or assume long is 32 bits. Validate ranges before narrowing conversions.
Explicit casts document intentional conversions; they do not replace checks.
Use sizeof(*pointer) when allocating a single object. Do not cast malloc.

Document ownership at API boundaries. Match malloc/free and Xlib/XFree.
Handle allocation and API failures, release partially acquired resources, and
leave output arguments untouched on rejected requests. Accept NULL only where
the API documents or historically supports it. Use const for read-only data.
Do not silently change public ABI during cleanup. In particular the legacy
DtXinerama unsigned coordinate API remains unsigned, including conversion of
negative monitor origins; a signed replacement requires a separate API.

Build maintained C with -Wall -Wextra -Wpedantic; use -Wconversion, -Wshadow,
and -Wstrict-prototypes for migrated libraries. Treat warnings as errors on
ported targets. Do not suppress pointer-width warnings or apply global flags
to hide migration defects. Keep flags and dependencies target-local in CMake.

All tests belong in tests/<component>. Verify observable contracts, invalid
inputs, ownership, and boundary conditions. Tests must still execute their
checks in Release builds (do not use assert for test checks). Use CTest.
Generated files, test executables, logs, and temporary products belong under
build/. bin/ is exclusively the installed filesystem tree.

Runtime paths come from the CMake configuration, with architecture-independent
assets under share/dt and internal executables under libexec/cde. Use native
CMake templates for data files; preserve quoting and physical continuation
lines in embedded shell commands. Environment variables and password database
lookups can both be absent: check their results before reading strings.

A 64-bit process does not imply that an existing disk or RPC field should
widen. NetISAM disk integers remain signed 32-bit; decode them with explicit
sign extension and test the bytes as well as round trips. Changing a stored
format requires an explicit compatibility decision.

ToolTalk database keys use an explicit 16-byte layout; access-control words
are 32-bit values even though Linux long is 64 bits. Use memcpy to load or
store potentially unaligned fields, followed by explicit byte-order conversion.
Use memmove when source and destination ranges can overlap, including B-tree
entry shifts. Keep regression coverage for insertion, deletion and reopen.

Linux PAM passes an array of message pointers to a conversation function.
Allocate one response per message, handle informational messages, and release
all partial responses on failure. A reused PAM handle must receive the new
identity before authentication. Keep conversation data valid for the call
and clear borrowed password pointers afterwards.

Keep private headers under lib/<component>; install only public SDK headers.
Versioned or configured headers are generated under build/ and installed
from there. Declare generator outputs and dependencies explicitly so a clean
build and an incremental build follow the same dependency graph. Tools that
write alongside their input must receive a copy in the build tree.

Password verification and account policy are separate PAM operations. The
login manager must check both before creating a session. Screen unlocking
uses authentication without invoking a new login session's account stack.

Screen and monitor geometry is runtime data. Handle RandR notifications and
update Xlib's screen dimensions before using cached display-size macros.
Keep physical/logical monitor regions separate from CDE workspaces, update
inactive workspaces too, and preserve a maximized window's normal restore
geometry across resolution changes. Monitor origins use signed coordinates.

Keep the last applied monitor layout separate from fresh placement queries.
Framebuffer and CRTC changes can arrive separately; calculate panel anchoring
against each layout clipped to its corresponding framebuffer bounds.

Display geometry can change between an X11 query and its matching request.
Retry stale configuration replies using fresh state and a bounded retry delay;
a transient resize mismatch must not terminate the desktop session.

Distinguish elevated-group installation checks from ordinary file access.
Keep validation for elevated execution groups; user-owned mailboxes opened by
an ordinary process remain subject to Linux file permissions. Application
launch tests must verify the main window rather than accepting an error dialog.

Treat runtime scripts and registration files as installation dependencies.
Configure path-bearing templates in the build tree and install them through
CMake; use PROGRAMS for executable scripts. Validate a clean DESTDIR so old
staged files cannot conceal missing install rules.

/*-
 * Copyright (c) 2010, 2013 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by David A. Holland.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Config for predefined macros. If this doesn't do what you want you
 * can set any or all of the CONFIG_ defines from the compiler command
 * line; or patch the list in main.c; or both.
 */

/*
 * Paths
 */

#ifndef CONFIG_LOCALINCLUDE
#define CONFIG_LOCALINCLUDE "/usr/local/include"
#endif

#ifndef CONFIG_SYSTEMINCLUDE
#define CONFIG_SYSTEMINCLUDE "/usr/include"
#endif

/*
 * Operating system
 */

#ifndef CONFIG_OS
#if defined(__DragonFly__)
#define CONFIG_OS "__DragonFly__"
#define CONFIG_OS_2 "__unix__"
#else
#define CONFIG_OS "__linux__"
#endif
#endif

/*
 * CPU
 */

#ifndef CONFIG_CPU
#define CONFIG_CPU "__x86_64__"
#define CONFIG_CPU_2 "__amd64__"
#endif

/*
 * Other stuff
 */

#ifndef CONFIG_SIZE
#ifdef __LP64__
#define CONFIG_SIZE "__LP64__"
#else
#define CONFIG_SIZE "__ILP32__"
#endif
#endif

#ifndef CONFIG_BINFMT
#ifdef __ELF__
#define CONFIG_BINFMT "__ELF__"
#endif
#endif

/*
 * We are __TRADCPP__ by default, but if you want to masquerade as
 * some other compiler this is a convenient place to change it.
 */

#ifndef CONFIG_COMPILER
#define CONFIG_COMPILER "__TRADCPP__"
#define CONFIG_COMPILER_MINOR "__TRADCPP_MINOR__"
#endif

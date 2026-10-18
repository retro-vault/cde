/***********************************************************************
*                                                                      *
*               This software is part of the ast package               *
*          Copyright (c) 1985-2011 AT&T Intellectual Property          *
*          Copyright (c) 2020-2022 Contributors to ksh 93u+m           *
*                      and is licensed under the                       *
*                 Eclipse Public License, Version 2.0                  *
*                                                                      *
*                A copy of the License is available at                 *
*      https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html      *
*         (with md5 checksum 84283fa8859daf213bdda5a9f8d1be1d)         *
*                                                                      *
*                 Glenn Fowler <gsf@research.att.com>                  *
*                  David Korn <dgk@research.att.com>                   *
*                   Phong Vo <kpv@research.att.com>                    *
*                  Martijn Dekker <martijn@inlv.org>                   *
*                                                                      *
***********************************************************************/
/*
 * K. P. Vo
 * G. S. Fowler
 * AT&T Research
 *
 * ``the best'' combined linear congruent checksum/hash/PRNG
 */

#ifndef _HASHPART_H
#define _HASHPART_H

#define HASH_ADD(h)	(0x9c39c33dL)


#define HASH_MPY(h)	((h)*0x63c63cd9L)


#define HASHPART(h,c)	(h = HASH_MPY(h) + HASH_ADD(h) + (c))

#endif

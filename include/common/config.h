/*
 * include/common/config.h
 * This files contains most of the user-configurable settings.
 *
 * Copyright (C) 2000-2009 Willy Tarreau - w@1wt.eu
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation, version 2.1
 * exclusively.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _COMMON_CONFIG_H
#define _COMMON_CONFIG_H

#include <common/compiler.h>
#include <common/compat.h>
#include <common/defaults.h>

/* this reduces the number of calls to select() by choosing appropriate
 * sheduler precision in milliseconds. It should be near the minimum
 * time that is needed by select() to collect all events. All timeouts
 * are rounded up by adding this value prior to pass it to select().
 */
#define SCHEDULER_RESOLUTION    9

/* CONFIG_HAP_MEM_OPTIM
 * This enables use of memory pools instead of malloc()/free(). There
 * is no reason to disable it, except perhaps for rare debugging.
 */
#ifndef   CONFIG_HAP_NO_MEM_OPTIM
#  define CONFIG_HAP_MEM_OPTIM
#endif /* CONFIG_HAP_NO_MEM_OPTIM */

#ifdef USE_THREAD
#define THREAD_LOCAL __thread
#else
#define THREAD_LOCAL
#endif

/* On architectures supporting threads and double-word CAS, we can implement
 * lock-less memory pools. This isn't supported for debugging modes however.
 */
#if !defined(DEBUG_NO_LOCKLESS_POOLS) && defined(USE_THREAD) && defined(HA_HAVE_CAS_DW) && !defined(DEBUG_UAF)
#define CONFIG_HAP_LOCKLESS_POOLS
#endif

/* CONFIG_HAP_INLINE_FD_SET
 * This makes use of inline FD_* macros instead of calling equivalent
 * functions. Benchmarks on a Pentium-M show that using functions is
 * generally twice as fast. So it's better to keep this option unset.
 */
//#undef  CONFIG_HAP_INLINE_FD_SET

#endif /* _COMMON_CONFIG_H */

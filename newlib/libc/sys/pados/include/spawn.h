/*
 * Copyright (C) 2026 Kurt Skauen. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _SPAWN_H_
#define _SPAWN_H_

#include <_ansi.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/_types.h>
#define __need_sigset_t
#include <signal.h>

struct sched_param;

typedef struct PPosixSpawnAttribs*      posix_spawnattr_t;
typedef struct PPosixSpawnFileActions*  posix_spawn_file_actions_t;

#define POSIX_SPAWN_RESETIDS        0x01
#define POSIX_SPAWN_SETPGROUP       0x02
#define POSIX_SPAWN_SETSIGDEF       0x04
#define POSIX_SPAWN_SETSIGMASK      0x08
#define POSIX_SPAWN_SETSCHEDPARAM   0x10
#define POSIX_SPAWN_SETSCHEDULER    0x20
#define POSIX_SPAWN_SETSID          0x80


_BEGIN_STD_C

/*
 * Spawn routines
 */
int posix_spawn(pid_t* __restrict outPID,
    const char* __restrict path,
    const posix_spawn_file_actions_t* __restrict fileActions,
    const posix_spawnattr_t* __restrict spawnAttr,
    char* const argv[],
    char* const envp[]
);

int posix_spawnp(pid_t* __restrict outPID,
    const char* __restrict name,
    const posix_spawn_file_actions_t* __restrict fileActions,
    const posix_spawnattr_t* __restrict spawnAttr,
    char* const argv[],
    char* const envp[]
);

/*
 * File descriptor actions
 */
int posix_spawn_file_actions_init(posix_spawn_file_actions_t* actions);
int posix_spawn_file_actions_destroy(posix_spawn_file_actions_t* actions);

int posix_spawn_file_actions_addopen(posix_spawn_file_actions_t* __restrict actions, int fd, const char* __restrict path, int oflag, mode_t mode);
int posix_spawn_file_actions_adddup2(posix_spawn_file_actions_t* actions, int fd, int newfd);
int posix_spawn_file_actions_addclose(posix_spawn_file_actions_t* actions, int fd);
#if __POSIX_VISIBLE >= 202405
int posix_spawn_file_actions_addchdir(posix_spawn_file_actions_t* __restrict actions, const char* __restrict path);
int posix_spawn_file_actions_addfchdir(posix_spawn_file_actions_t* __restrict actions, int fd);
#endif
#if __MISC_VISIBLE || __GNU_VISIBLE
int posix_spawn_file_actions_addchdir_np(posix_spawn_file_actions_t* __restrict actions, const char* __restrict path);
int posix_spawn_file_actions_addfchdir_np(posix_spawn_file_actions_t* __restrict actions, int fd);
#endif

/*
 * Spawn attributes
 */
int posix_spawnattr_init(posix_spawnattr_t* attr);
int posix_spawnattr_destroy(posix_spawnattr_t* attr);

int posix_spawnattr_getflags(const posix_spawnattr_t* __restrict attr, short* __restrict flags);
int posix_spawnattr_setflags(posix_spawnattr_t* attr, short flags);

int posix_spawnattr_getpgroup(const posix_spawnattr_t* __restrict attr, pid_t* __restrict pgroup);
int posix_spawnattr_setpgroup(posix_spawnattr_t* attr, pid_t pgroup);

int posix_spawnattr_getschedparam(const posix_spawnattr_t* __restrict attr, struct sched_param* __restrict sp);
int posix_spawnattr_setschedparam(posix_spawnattr_t* __restrict attr, const struct sched_param* __restrict sp);

int posix_spawnattr_getschedpolicy(const posix_spawnattr_t* __restrict attr, int* __restrict policy);
int posix_spawnattr_setschedpolicy(posix_spawnattr_t* attr, int policy);

int posix_spawnattr_getsigdefault(const posix_spawnattr_t* __restrict attr, sigset_t* __restrict sigdef);
int posix_spawnattr_setsigdefault(posix_spawnattr_t* __restrict attr, const sigset_t* __restrict sigdef);

int posix_spawnattr_getsigmask(const posix_spawnattr_t* __restrict attr, sigset_t* __restrict sigmask);
int posix_spawnattr_setsigmask(posix_spawnattr_t* __restrict attr, const sigset_t* __restrict sigmask);

_END_STD_C

#endif /* !_SPAWN_H_ */

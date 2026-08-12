/*
 * Copyright (C) 2025 Kurt Skauen. All rights reserved.
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

#include <unistd.h>
#include <pwd.h>
#include <stdint.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include "sys/pados_syscalls.h"
#include <sched.h>


__attribute__((weak)) void* __aeabi_read_tp(void) { return NULL; }
__attribute__((weak)) void _start(void);
__attribute__((weak)) void* _sbrk(ptrdiff_t nbytes) { return nullptr; }

int __attribute__((weak)) pthread_setcancelstate(int state, int* oldstate) { return -1;  }

char* __attribute__((weak)) getlogin(void)
{
    errno = ENOSYS;
    return NULL;
}

struct passwd* __attribute__((weak)) getpwnam(const char* name)
{
    errno = ENOSYS;
    return NULL;
}

struct passwd* __attribute__((weak)) getpwuid(uid_t userID)
{
    errno = ENOSYS;
    return NULL;
}

int __attribute__((weak)) issetugid(void)
{
    return 0;
}

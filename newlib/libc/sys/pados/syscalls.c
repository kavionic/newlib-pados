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
#include <stdint.h>
#include <errno.h>

#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <sys/stat.h>
#include "sys/pados_syscalls.h"
#include <sched.h>


_off64_t _lseek64_r(struct _reent*, int, _off64_t, int)
{
    errno = ENOSYS;
    return -1;
}

//int _fstat64_r(struct _reent*, int, struct stat64*)
//{
//    errno = ENOSYS;
//    return -1;
//}
//
//int _open64_r(struct _reent*, const char*, int, int)
//{
//    errno = ENOSYS;
//    return -1;
//}
//
//int _stat64_r(struct _reent*, const char*, struct stat64*)
//{
//    errno = ENOSYS;
//    return -1;
//}

long sysconf(int name)
{
    switch (name)
    {
        case _SC_PAGESIZE:
#ifdef SMALL_MEMORY
            return 128;
#else
            return 4096;
#endif

        default:
            errno = EINVAL;
            return -1;
    }
    return -1; /* Can't get here */
}

int sched_yield(void)
{
    return 0;
}
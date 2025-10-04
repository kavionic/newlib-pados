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

#include <sys/types.h>
#include <sys/time.h>
#include <utime.h>
#include "sys/pados_syscalls.h"

int futimens(int fd, const struct timespec times[2])
{
    uint32_t mask = 0;
    struct stat newStat;
    if (times != NULL)
    {
        if (times[0].tv_nsec != UTIME_OMIT)
        {
            if (times[0].tv_nsec != UTIME_NOW) {
                newStat.st_atim = times[0];
            } else {
                clock_gettime(CLOCK_REALTIME, &newStat.st_atim);
            }
            mask = WSTAT_ATIME;
        }
        if (times[1].tv_nsec != UTIME_OMIT)
        {
            if (times[1].tv_nsec != UTIME_NOW) {
                newStat.st_mtim = times[1];
            } else if (times[0].tv_nsec == UTIME_NOW) {
                newStat.st_mtim = newStat.st_atim;
            } else {
                clock_gettime(CLOCK_REALTIME, &newStat.st_mtim);
            }
            mask = WSTAT_MTIME;
        }
    }
    else
    {
        clock_gettime(CLOCK_REALTIME, &newStat.st_atim);
        newStat.st_mtim = newStat.st_atim;
        mask = WSTAT_ATIME | WSTAT_MTIME;
    }
    if (mask != 0) {
        return __write_stat(fd, &newStat, mask);
    } else {
        return 0;
    }
}

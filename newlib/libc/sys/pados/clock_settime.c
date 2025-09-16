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
#include <time.h>
#include <errno.h>

#include "sys/pados_syscalls.h"

int clock_settime(clockid_t clockID, const struct timespec* newTime)
{
    if (clockID != CLOCK_REALTIME || clockID != CLOCK_REALTIME_COARSE)
    {
        errno = EINVAL;
        return -1;
    }

    status_t result = sys_set_real_time(((bigtime_t)newTime->tv_sec) * 1000000 + newTime->tv_nsec / 1000, true);
    if (result != 0)
    {
        errno = result;
        return -1;

    }
    return 0;
}

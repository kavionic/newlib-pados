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

#include <sys/pados_timeutils.h>
#include <sys/pados_syscalls.h>

int nanosleep(const struct timespec* requested, struct timespec* remaining)
{
    const bigtime_t nSeconds = timespec_to_nanos(requested);
    if (remaining != NULL)
    {
        const bigtime_t startTime = __get_system_time();
        if (__snooze_ns(nSeconds) != 0)
        {
            const bigtime_t lapsedNs = __get_system_time() - startTime;
            const bigtime_t remainingNs = nSeconds - lapsedNs;
            if (remainingNs > 0)
            {
                *remaining = nanos_to_timespec(remainingNs);
                errno = EINTR;
                return -1;
            }
        }
        remaining->tv_sec = 0;
        remaining->tv_nsec = 0;
        return 0;
    }
    else
    {
        return __snooze_ns(nSeconds);
    }
}

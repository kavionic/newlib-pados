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

#include <sys/pados_timeutils.h>
#include <sys/pados_syscalls.h>

int clock_gettime(clockid_t clk_id, struct timespec* tp)
{
    const bigtime_t timeOffset = sys_get_clock_time_offset(clk_id);

    if (clk_id == CLOCK_MONOTONIC_COARSE || clk_id == CLOCK_REALTIME_COARSE)
    {
        const bigtime_t systemTime_uS = sys_get_system_time() + timeOffset;
        *tp = micros_to_timespec(systemTime_uS);
    }
    else
    {
        const timespec_t offsetSpec = micros_to_timespec(timeOffset);
        const bigtime_t systemTime_nS = sys_get_system_time_hires();

        *tp = nanos_to_timespec(systemTime_nS);
        tp->tv_sec  += offsetSpec.tv_sec;
        tp->tv_nsec += offsetSpec.tv_nsec;
        if (tp->tv_nsec >= 1000000000)
        {
            tp->tv_sec++;
            tp->tv_nsec -= 1000000000;
        }
    }
    return 0;
}

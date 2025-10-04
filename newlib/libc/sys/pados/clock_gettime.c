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
    if (clk_id == CLOCK_MONOTONIC_COARSE || clk_id == CLOCK_REALTIME_COARSE)
    {
        const bigtime_t systemTime = __get_clock_time(clk_id);
        *tp = nanos_to_timespec(systemTime);
    }
    else
    {
        const bigtime_t systemTime = __get_clock_time_hires(clk_id);
        *tp = nanos_to_timespec(systemTime);
    }
    return 0;
}

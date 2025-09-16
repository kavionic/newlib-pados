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

#include <sys/pados_timeutils.h>
#include <sys/pados_syscalls.h>


int clock_getres(clockid_t clk_id, struct timespec* tp)
{
    bigtime_t resolutionNanos;
    status_t result = sys_get_clock_resolution(clk_id, &resolutionNanos);
    if (result == 0) {
        *tp = nanos_to_timespec(resolutionNanos);
    }
    return result;
}

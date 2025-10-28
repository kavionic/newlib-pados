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

#pragma once

#include <sys/pados_error_codes.h>

#ifdef __cplusplus
#include <System/TimeValue.h>
extern "C" {
#endif

time_t      get_monotonic_time_ns();
time_t      get_monotonic_time_hires_ns();

time_t      get_real_time_ns();
time_t      get_real_time_hires_ns();
PErrorCode  set_real_time_ns(time_t time, bool updateRTC);

time_t      get_idle_time_ns();
time_t      get_total_irq_time_ns();

time_t      get_clock_time_ns(clockid_t clockID);
time_t      get_clock_time_hires_ns(clockid_t clockID);

time_t      get_clock_time_offset_ns(clockid_t clockID);

#ifdef __cplusplus
}

TimeValNanos get_monotonic_time();
TimeValNanos get_monotonic_time_hires();

TimeValNanos get_real_time();
TimeValNanos get_real_time_hires();
PErrorCode   set_real_time(TimeValNanos time, bool updateRTC);

TimeValNanos get_idle_time();
TimeValNanos get_total_irq_time();

TimeValNanos get_clock_time(clockid_t clockID);
TimeValNanos get_clock_time_hires(clockid_t clockID);

TimeValNanos get_clock_time_offset(clockid_t clockID);

#endif // __cplusplus

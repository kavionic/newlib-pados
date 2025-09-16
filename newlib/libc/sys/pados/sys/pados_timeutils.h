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


#define MAX_CLOCKS  (16)

/* Conversions for per-process and per-thread clocks */
#define CLOCKID(cid)                ((cid) % MAX_CLOCKS)

#define PID_TO_CLOCKID(pid)         ((pid) * MAX_CLOCKS + CLOCK_PROCESS_CPUTIME_ID)
#define CLOCKID_TO_PID(cid)         (((cid) - CLOCK_PROCESS_CPUTIME_ID) / MAX_CLOCKS)
#define CLOCKID_IS_PROCESS(cid)     (CLOCKID(cid) == CLOCK_PROCESS_CPUTIME_ID)

#define THREADID_TO_CLOCKID(tid)    ((tid) * MAX_CLOCKS + CLOCK_THREAD_CPUTIME_ID)
#define CLOCKID_TO_THREADID(cid)    (((cid) - CLOCK_THREAD_CPUTIME_ID) / MAX_CLOCKS)
#define CLOCKID_IS_THREAD(cid)      (CLOCKID(cid) == CLOCK_THREAD_CPUTIME_ID)

inline timespec_t micros_to_timespec(bigtime_t micros) { return (timespec_t){ .tv_sec = (micros / 1000000), .tv_nsec = (long int)((micros % 1000000) * 1000) }; }
inline bigtime_t timespec_to_micros(const timespec_t* time) { return ((bigtime_t)time->tv_sec) * 1000000 + time->tv_nsec / 1000; }

inline timespec_t nanos_to_timespec(bigtime_t nanos) { (timespec_t){ .tv_sec = nanos / 1000000000, .tv_nsec = nanos % 1000000000 }; }
inline bigtime_t timespec_to_nanos(const timespec_t* time) { return time->tv_sec * 1000000000 + time->tv_nsec; }

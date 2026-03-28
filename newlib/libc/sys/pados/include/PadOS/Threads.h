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

#include <stdint.h>
#include <sys/pados_types.h>
#include <sys/pados_error_codes.h>
#include <sys/pados_threads.h>

typedef enum
{
    THREAD_CANCEL_ENABLE,
    THREAD_CANCEL_DISABLE
} PThreadCancelState;

typedef enum
{
    THREAD_CANCEL_DEFERRED,
    THREAD_CANCEL_ASYNCHRONOUS
} PThreadCancelType;

typedef struct PThreadControlBlock
{
    void* Ptr1;
    void* Ptr2;
} PThreadControlBlock;

#ifdef __cplusplus
extern "C" {
#endif

extern PThreadControlBlock* __current_thread_control_block;

pid_t       get_thread_id();
PErrorCode  thread_spawn(pid_t* outHandle, const PThreadAttribs* attribs, ThreadEntryPoint_t entryPoint, void* arguments);
void        thread_exit(void* returnValue);
PErrorCode  thread_cancel(pid_t threadID);
void        thread_testcancel(void);
PErrorCode  thread_setcancelstate(PThreadCancelState state, PThreadCancelState* outOldState);
PErrorCode  thread_setcanceltype(PThreadCancelType type, PThreadCancelType* outOldType);

#ifdef __cplusplus
}
#endif

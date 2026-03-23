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

typedef struct PThreadControlBlock
{
    void* Ptr1;
    void* Ptr2;
} PThreadControlBlock;

#ifdef __cplusplus
extern "C" {
#endif

extern PThreadControlBlock* __current_thread_control_block;

PErrorCode thread_spawn(thread_id* outHandle, const PThreadAttribs* attribs, ThreadEntryPoint_t entryPoint, void* arguments);
void thread_exit(void* returnValue);

#ifdef __cplusplus
}
#endif

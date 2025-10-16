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

#include <sys/pados_syscalls.h>
#include <PadOS/Threads.h>
#include <PadOS/ThreadLocal.h>

PErrorCode thread_local_set(tls_id key, const void* value)
{
    if (key < 0 || key >= current_thread_control_block->TLSSlotCount) {
        return PErrorCode_InvalidArg;
    }
    current_thread_control_block->TLSSlots[key] = (void*)value;
    return PErrorCode_Success;
}

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

#include <stdarg.h>
#include "sys/pados_syscalls.h"
#include <PadOS/MessagePort.h>
#include <PadOS/SyscallReturns.h>

ssize_t message_port_receive(port_id handle, handler_id* targetHandler, int32_t* code, void* buffer, size_t bufferSize)
{
    return PSysRetUpdateErrno(__message_port_receive(handle, targetHandler, code, buffer, bufferSize));
}

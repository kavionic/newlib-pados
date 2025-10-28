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

#include <sys/types.h>
#include <sys/pados_types.h>
#include <sys/pados_error_codes.h>

#ifdef __cplusplus
extern "C" {
#endif

PErrorCode  message_port_create(port_id* outHandle, const char* name, int maxCount);
PErrorCode  message_port_duplicate(port_id* outNewHandle, port_id handle);
PErrorCode  message_port_delete(port_id handle);
PErrorCode  message_port_send(port_id handle, handler_id targetHandler, int32_t code, const void* data, size_t length);
PErrorCode  message_port_send_timeout_ns(port_id handle, handler_id targetHandler, int32_t code, const void* data, size_t length, bigtime_t timeout);
PErrorCode  message_port_send_deadline_ns(port_id handle, handler_id targetHandler, int32_t code, const void* data, size_t length, bigtime_t deadline);
ssize_t     message_port_receive(port_id handle, handler_id* targetHandler, int32_t* code, void* buffer, size_t bufferSize);
ssize_t     message_port_receive_timeout_ns(port_id handle, handler_id* targetHandler, int32_t* code, void* buffer, size_t bufferSize, bigtime_t timeout);
ssize_t     message_port_receive_deadline_ns(port_id handle, handler_id* targetHandler, int32_t* code, void* buffer, size_t bufferSize, bigtime_t deadline);

#ifdef __cplusplus
}
#endif

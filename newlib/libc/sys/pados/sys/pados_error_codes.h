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

#include <errno.h>

#ifdef __cplusplus
#define PCREAT_ERROR_CODE(NAME, ERRORCODE) NAME = ERRORCODE
enum class PErrorCode : int
#else
#define PCREAT_ERROR_CODE(NAME, ERRORCODE) PErrorCode_##NAME = ERRORCODE
typedef enum
#endif
{
    PCREAT_ERROR_CODE(Success,          0),
    PCREAT_ERROR_CODE(NoMemory,         ENOMEM),
    PCREAT_ERROR_CODE(NotImplemented,   ENOSYS),
    PCREAT_ERROR_CODE(InvalidArg,       EINVAL),
    PCREAT_ERROR_CODE(Busy,             EBUSY),
    PCREAT_ERROR_CODE(TryAgain,         EAGAIN),
    PCREAT_ERROR_CODE(Interrupted,      EINTR),
    PCREAT_ERROR_CODE(Timeout,          ETIMEDOUT),
    PCREAT_ERROR_CODE(Deadlock,         EDEADLK),
    PCREAT_ERROR_CODE(WouldBlock,       EWOULDBLOCK),
    PCREAT_ERROR_CODE(Exist,            EEXIST),
    PCREAT_ERROR_CODE(NoEntry,          ENOENT),
    PCREAT_ERROR_CODE(Overflow,         EOVERFLOW)
}
#ifdef __cplusplus
;
#else
PErrorCode;
#endif

#undef PCREAT_ERROR_CODE

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
#include <errno.h>
#include <sys/pados_error_codes.h>


typedef uint64_t PSysRetPair;

inline PSysRetPair PMakeSysRetPair(PErrorCode result, int32_t value) { return ((PSysRetPair)result) | ((PSysRetPair)value) << 32; }
inline PSysRetPair PMakeSysRetSuccess(int32_t value) { return ((PSysRetPair)0) | ((PSysRetPair)value) << 32; }
inline PSysRetPair PMakeSysRetFail(PErrorCode result) { return ((PSysRetPair)result); }

inline PErrorCode  PSysRetResult(PSysRetPair resultPair) { return (PErrorCode)(resultPair & 0xffffffff); }
inline int32_t     PSysRetValue(PSysRetPair resultPair) { return (int32_t)(resultPair >> 32); }

inline int32_t PSysRetUpdateErrno_impl(PSysRetPair result)
{
    if (PSysRetResult(result) != (PErrorCode)0)
    {
        errno = (int)PSysRetResult(result);
        return -1;
    }
    return PSysRetValue(result);
}

inline int PErrorCodeUpdateErrno_impl(PErrorCode result)
{
    if (result != (PErrorCode)0)
    {
        errno = (int)result;
        return -1;
    }
    return 0;
}

#define PErrorCodeUpdateErrno(x) \
({  _Static_assert(__builtin_types_compatible_p(__typeof__(x), PErrorCode), \
        "PErrorCodeUpdateErrno(x): argument must be PErrorCode");          \
    PErrorCodeUpdateErrno_impl((x));                                        \
})

#define PSysRetUpdateErrno(x) \
({  _Static_assert(__builtin_types_compatible_p(__typeof__(x), PSysRetPair), \
        "PSysRetUpdateErrno(x): argument must be PSysRetPair");              \
    PSysRetUpdateErrno_impl((x));                                            \
})

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
#include <sys/cdefs.h>
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


// (type,name) -> "type name" and -> "name"
#define PARG_DECL(a)  PARG_DECL_ a
#define PARG_DECL_(t, n) t n

#define PARG_NAME(a)  PARG_NAME_ a
#define PARG_NAME_(t, n) n

// Argument pack encodes a count as first element
#define PARGS0()                       (0)
#define PARGS1(a1)                     (1, a1)
#define PARGS2(a1,a2)                  (2, a1,a2)
#define PARGS3(a1,a2,a3)               (3, a1,a2,a3)
#define PARGS4(a1,a2,a3,a4)            (4, a1,a2,a3,a4)
#define PARGS5(a1,a2,a3,a4,a5)         (5, a1,a2,a3,a4,a5)
#define PARGS6(a1,a2,a3,a4,a5,a6)      (6, a1,a2,a3,a4,a5,a6)
#define PARGS7(a1,a2,a3,a4,a5,a6,a7)   (7, a1,a2,a3,a4,a5,a6,a7)

#define PARGC(args) PARGC_ args
#define PARGC_(n, ...) n

// Typed parameter list
#define PDECL_LIST(args)  PDECL_LIST_(PARGC(args), args)
#define PDECL_LIST_(n, args) __CONCAT(PDECL_LIST_, n) args
#define PDECL_LIST_0(n)                      void
#define PDECL_LIST_1(n,a1)                   PARG_DECL(a1)
#define PDECL_LIST_2(n,a1,a2)                PARG_DECL(a1), PARG_DECL(a2)
#define PDECL_LIST_3(n,a1,a2,a3)             PARG_DECL(a1), PARG_DECL(a2), PARG_DECL(a3)
#define PDECL_LIST_4(n,a1,a2,a3,a4)          PARG_DECL(a1), PARG_DECL(a2), PARG_DECL(a3), PARG_DECL(a4)
#define PDECL_LIST_5(n,a1,a2,a3,a4,a5)       PARG_DECL(a1), PARG_DECL(a2), PARG_DECL(a3), PARG_DECL(a4), PARG_DECL(a5)
#define PDECL_LIST_6(n,a1,a2,a3,a4,a5,a6)    PARG_DECL(a1), PARG_DECL(a2), PARG_DECL(a3), PARG_DECL(a4), PARG_DECL(a5), PARG_DECL(a6)
#define PDECL_LIST_7(n,a1,a2,a3,a4,a5,a6,a7) PARG_DECL(a1), PARG_DECL(a2), PARG_DECL(a3), PARG_DECL(a4), PARG_DECL(a5), PARG_DECL(a6), PARG_DECL(a7)

// Name-only argument list
#define PNAME_LIST(args)  PNAME_LIST_(PARGC(args), args)
#define PNAME_LIST_(n, args) __CONCAT(PNAME_LIST_, n) args
#define PNAME_LIST_0(n)                    /* empty */
#define PNAME_LIST_1(n,a1)                   PARG_NAME(a1)
#define PNAME_LIST_2(n,a1,a2)                PARG_NAME(a1), PARG_NAME(a2)
#define PNAME_LIST_3(n,a1,a2,a3)             PARG_NAME(a1), PARG_NAME(a2), PARG_NAME(a3)
#define PNAME_LIST_4(n,a1,a2,a3,a4)          PARG_NAME(a1), PARG_NAME(a2), PARG_NAME(a3), PARG_NAME(a4)
#define PNAME_LIST_5(n,a1,a2,a3,a4,a5)       PARG_NAME(a1), PARG_NAME(a2), PARG_NAME(a3), PARG_NAME(a4), PARG_NAME(a5)
#define PNAME_LIST_6(n,a1,a2,a3,a4,a5,a6)    PARG_NAME(a1), PARG_NAME(a2), PARG_NAME(a3), PARG_NAME(a4), PARG_NAME(a5), PARG_NAME(a6)
#define PNAME_LIST_7(n,a1,a2,a3,a4,a5,a6,a7) PARG_NAME(a1), PARG_NAME(a2), PARG_NAME(a3), PARG_NAME(a4), PARG_NAME(a5), PARG_NAME(a6), PARG_NAME(a7)

/*
 * Copyright (C) 2025-2026 Kurt Skauen. All rights reserved.
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
#include <string.h>

#ifdef __cplusplus
#define PCREAT_ERROR_CODE(NAME, ERRORCODE) NAME = ERRORCODE
enum class PErrorCode : int
#else
#define PCREAT_ERROR_CODE(NAME, ERRORCODE) PErrorCode_##NAME = ERRORCODE
typedef enum
#endif
{
    PCREAT_ERROR_CODE(Success,              0),
    PCREAT_ERROR_CODE(NOMEM,                ENOMEM),
    PCREAT_ERROR_CODE(NOSYS,                ENOSYS),
    PCREAT_ERROR_CODE(INVAL,                EINVAL),
    PCREAT_ERROR_CODE(MFILE,                EMFILE),
    PCREAT_ERROR_CODE(NOTTY,                ENOTTY),
    PCREAT_ERROR_CODE(FTYPE,                EFTYPE),
    PCREAT_ERROR_CODE(RANGE,                ERANGE),
    PCREAT_ERROR_CODE(FAULT,                EFAULT),
    PCREAT_ERROR_CODE(BUSY,                 EBUSY),
    PCREAT_ERROR_CODE(AGAIN,                EAGAIN),
    PCREAT_ERROR_CODE(INTR,                 EINTR),
    PCREAT_ERROR_CODE(TIMEDOUT,             ETIMEDOUT),
    PCREAT_ERROR_CODE(DEADLK,               EDEADLK),
    PCREAT_ERROR_CODE(WOULDBLOCK,           EWOULDBLOCK),
    PCREAT_ERROR_CODE(EXIST,                EEXIST),
    PCREAT_ERROR_CODE(NOENT,                ENOENT),
    PCREAT_ERROR_CODE(SRCH,                 ESRCH),
    PCREAT_ERROR_CODE(OVERFLOW,             EOVERFLOW),
    PCREAT_ERROR_CODE(BADF,                 EBADF),
    PCREAT_ERROR_CODE(CHILD,                ECHILD),
    PCREAT_ERROR_CODE(ISDIR,                EISDIR),
    PCREAT_ERROR_CODE(NOTDIR,               ENOTDIR),
    PCREAT_ERROR_CODE(NOTEMPTY,             ENOTEMPTY),
    PCREAT_ERROR_CODE(NODEV,                ENODEV),
    PCREAT_ERROR_CODE(XDEV,                 EXDEV),
    PCREAT_ERROR_CODE(IO,                   EIO),
    PCREAT_ERROR_CODE(PERM,                 EPERM),
    PCREAT_ERROR_CODE(ACCES,                EACCES),
    PCREAT_ERROR_CODE(FBIG,                 EFBIG),
    PCREAT_ERROR_CODE(NOSPC,                ENOSPC),
    PCREAT_ERROR_CODE(PIPE,                 EPIPE),
    PCREAT_ERROR_CODE(CONNREFUSED,          ECONNREFUSED),
    PCREAT_ERROR_CODE(NAMETOOLONG,          ENAMETOOLONG),
    PCREAT_ERROR_CODE(LOOP,                 ELOOP),
    PCREAT_ERROR_CODE(ROFS,                 EROFS),
    PCREAT_ERROR_CODE(SPIPE,                ESPIPE),

    PCREAT_ERROR_CODE(RestartSyscall,       __ELASTERROR + 1),
    PCREAT_ERROR_CODE(_SIZEEXTEND,          0x7fffffff)
}
#ifdef __cplusplus
;
#else
PErrorCode;
#endif

inline const char* p_strerror(PErrorCode error) { return strerror((int)error); }

#undef PCREAT_ERROR_CODE

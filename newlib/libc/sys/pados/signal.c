/*
 * Copyright (C) 2026 Kurt Skauen. All rights reserved.
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

#include <unistd.h>
#include <stdint.h>
#include <errno.h>

#include <sys/pados_syscalls.h>
#include <PadOS/SyscallReturns.h>

_sig_func_ptr signal(int sigNum, _sig_func_ptr func)
{
    const PSysRetPair result = __signal(sigNum, func);
    if (PSysRetResult(result) == PErrorCode_Success)
    {
        return (_sig_func_ptr)PSysRetValue(result);
    }
    else
    {
        errno = PSysRetResult(result);
        return SIG_ERR;
    }
}

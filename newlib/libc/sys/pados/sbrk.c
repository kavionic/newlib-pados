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

#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <sys/pados_syscalls.h>
#include <PadOS/SyscallReturns.h>

#include "reent.h"

void* _sbrk_r(struct _reent*, ptrdiff_t size)
{
    _Static_assert(
        sizeof(PSysRetUpdateErrno((PSysRetPair)0)) >= sizeof(void*),
        "PSysRetUpdateErrno must return a type at least pointer-sized."
    );
    return (void*)PSysRetUpdateErrno(__sbrk(size));
}

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

#include "reent.h"
#include "sys/pados_syscalls.h"

_ssize_t _read_r(struct _reent* reent, int fd, void* buffer, size_t length)
{
    _ssize_t bytesRead;
    const PErrorCode result = __read(fd, buffer, length, &bytesRead);
    if (result != PErrorCode_Success)
    {
        _REENT_ERRNO(reent) = result;
        return -1;
    }
    return bytesRead;
}

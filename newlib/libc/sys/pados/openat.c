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

#include "reent.h"
#include <stdarg.h>
#include "sys/pados_syscalls.h"

int openat(int dirfd, const char* path, int flags, ...)
{
    va_list ap;
    mode_t mode;

    va_start(ap, flags);
    mode = va_arg(ap, mode_t);
    va_end(ap);

    return sys_openat(dirfd, path, flags, mode);
}

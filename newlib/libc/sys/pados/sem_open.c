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

#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/pados_syscalls.h>

sem_t* sem_open(const char* name, int oflag, ...)
{
    mode_t mode = 0;
    unsigned int value = 0;
    va_list ap;

    sem_t* const semaphore = malloc(sizeof(sem_t));
    if (semaphore == nullptr)
    {
        errno = ENOMEM;
        return SEM_FAILED;
    }

    if (oflag & O_CREAT)
    {
        va_start(ap, oflag);
        mode = va_arg(ap, mode_t) & ~S_IXUSR;
        value = va_arg(ap, unsigned int);
        va_end(ap);
    }

    const PErrorCode result = __semaphore_create_public(semaphore, name, CLOCK_REALTIME_COARSE, oflag, mode, value);
    if (result == PErrorCode_Success)
    {
        return semaphore;
    }

    free(semaphore);
    errno = result;
    return SEM_FAILED;
}

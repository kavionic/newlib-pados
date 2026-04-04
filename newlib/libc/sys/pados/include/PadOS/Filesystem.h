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
#include <sys/pados_error_codes.h>

#ifdef __cplusplus
extern "C" {
#endif

int reopen_file(int oldHandle, int openFlags);

PErrorCode device_control(int handle, int request, const void* inData, size_t inDataLength, void* outData, size_t outDataLength);

PErrorCode rewind_directory(int handle);
PErrorCode get_directory_path(int handle, char* buffer, size_t bufferSize);

PErrorCode mount(const char* devicePath, const char* directoryPath, const char* filesystemName, uint32_t flags, const char* args, size_t argLength);

#ifdef __cplusplus
}

#include <sys/unistd.h>
#include <sys/fcntl.h>
#include <sys/pados_syscalls.h>
#include <System/ExceptionHandling.h>

inline int open_trw(const char* path, int flags, int mode = 0)
{
    return PERROR_SYSRET_THROW_ON_FAIL(____open(path, flags, mode));
}

inline int read_trw(int file, void* buffer, size_t length)
{
    return PERROR_SYSRET_THROW_ON_FAIL(___read(file, buffer, length));
}

inline int write_trw(int file, const void* buffer, size_t length)
{
    return PERROR_SYSRET_THROW_ON_FAIL(___write(file, buffer, length));
}

inline void device_control_trw(int handle, int request, const void* inData, size_t inDataLength, void* outData, size_t outDataLength)
{
    PERROR_ERRORCODE_THROW_ON_FAIL(device_control(handle, request, inData, inDataLength, outData, outDataLength));
}

inline void rewind_directory_trw(int handle)
{
    PERROR_ERRORCODE_THROW_ON_FAIL(rewind_directory(handle));
}

inline void get_directory_path_trw(int handle, char* buffer, size_t bufferSize)
{
    PERROR_ERRORCODE_THROW_ON_FAIL(get_directory_path(handle, buffer, bufferSize));
}

inline void mount_trw(const char* devicePath, const char* directoryPath, const char* filesystemName, uint32_t flags, const char* args, size_t argLength)
{
    PERROR_ERRORCODE_THROW_ON_FAIL(mount(devicePath, directoryPath, filesystemName, flags, args, argLength));
}

#endif // __cplusplus

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

#include <stddef.h>
#include <inttypes.h>

typedef int      handle_id;
typedef int      thread_id;
typedef int      sem_id;
typedef int      port_id;
typedef int      handler_id;
typedef int      tls_id;
typedef int      fs_id;
typedef int64_t  bigtime_t;
typedef int      status_t;
typedef int64_t  off64_t;
typedef uint64_t size64_t;
typedef int64_t  ssize64_t;

typedef uint16_t wchar16_t;

#ifdef __cpp_constexpr
constexpr handler_id INVALID_HANDLE = -1;
#else
#define INVALID_HANDLE ((handler_id)-1)
#endif


#ifdef __cpp_constexpr
constexpr
#else
static const
#endif
size_t		INVALID_INDEX = (size_t)-1;

#ifdef __cpp_constexpr
constexpr size_t OS_NAME_LENGTH = 32;
#else
#define OS_NAME_LENGTH ((size_t)32)
#endif

static const uint32_t WSTAT_MODE  = 0x0001;
static const uint32_t WSTAT_UID   = 0x0002;
static const uint32_t WSTAT_GID   = 0x0004;
static const uint32_t WSTAT_SIZE  = 0x0008;
static const uint32_t WSTAT_ATIME = 0x0010;
static const uint32_t WSTAT_MTIME = 0x0020;
static const uint32_t WSTAT_CTIME = 0x0040;
static const uint32_t WSTAT_MASK  = 0x007f;

static const uint32_t WFSSTAT_NAME = 0x0001;

static const uint32_t  FSINFO_VERSION = 1;


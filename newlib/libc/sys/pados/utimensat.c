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

#include <time.h>
#include <utime.h>
#include <fcntl.h>
#include <sys/types.h>
#include "sys/pados_syscalls.h"

int utimensat(int dirfd, const char* path, const struct timespec times[2], int flags)
{
    //    if (flags & AT_SYMLINK_NOFOLLOW) {
    //    }
    int fd = sys_openat(dirfd, path, O_WRONLY, 0);
    if (fd < 0) {
        return -1;
    }
    int result = futimens(fd, times);
    sys_close(fd);
    return result;
}

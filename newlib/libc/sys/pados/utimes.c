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

int utimes(const char* path, const struct timeval times[2])
{
    if (times != nullptr)
    {
        timespec_t timeSpecs[2];
        for (size_t i = 0; i < 2; ++i)
        {
            timeSpecs[0].tv_sec = times[0].tv_sec;
            timeSpecs[0].tv_nsec = times[0].tv_usec * 1000;
        }
        return utimensat(AT_FDCWD, path, timeSpecs, 0);
    }
    else
    {
        return utimensat(AT_FDCWD, path, NULL, 0);
    }
}

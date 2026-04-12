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

#include <signal.h>
#include <errno.h>

#undef sigemptyset
int sigemptyset(sigset_t* set)
{
    *set = (sigset_t)0;
    return 0;
}

#undef sigfillset
int sigfillset(sigset_t* set)
{
    *set = ~((sigset_t)0);
    return 0;
}

#undef sigaddset
int sigaddset(sigset_t* set, int signo)
{
    if (signo >= (NSIG + NRTSIG) || signo <= 0)
    {
        errno = EINVAL;
        return -1;
    }
    *set |= 1 << (signo - 1);
    return 0;
}

#undef sigdelset
int sigdelset(sigset_t* set, int signo)
{
    if (signo >= (NSIG + NRTSIG) || signo <= 0)
    {
        errno = EINVAL;
        return -1;
    }
    *set &= ~(1 << (signo - 1));
    return 0;
}

#undef sigismember
int sigismember(const sigset_t* set, int signo)
{
    if (signo >= (NSIG + NRTSIG) || signo <= 0)
    {
        errno = EINVAL;
        return -1;
    }

    if (*set & (1 << (signo - 1))) {
        return 1;
    } else {
        return 0;
    }
}

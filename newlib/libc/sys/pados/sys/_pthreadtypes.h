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

#ifndef _SYS__PTHREADTYPES_H_
#define	_SYS__PTHREADTYPES_H_

#include <sys/pados_types.h>
#include <sys/sched.h>

typedef thread_id   pthread_t;
typedef sem_id      pthread_mutex_t;
typedef sem_id      pthread_rwlock_t;
typedef handle_id   pthread_cond_t;
typedef tls_id      pthread_key_t;
typedef int         pthread_once_t;
typedef int         pthread_spinlock_t;

#define PTHREAD_SCOPE_PROCESS   0
#define PTHREAD_SCOPE_SYSTEM    1

#define PTHREAD_INHERIT_SCHED   1
#define PTHREAD_EXPLICIT_SCHED  2

#define PTHREAD_CREATE_DETACHED 0
#define PTHREAD_CREATE_JOINABLE 1

#define PTHREAD_STACK_MIN 200

typedef struct
{
  int       is_initialized;
  void*     stackaddr;
  int       stacksize;
  int       contentionscope;
  int       inheritsched;
  int       schedpolicy;
  size_t    guardsize;
  int       detachstate;
  struct sched_param schedparam;
} pthread_attr_t;


#if defined(_POSIX_THREAD_PROCESS_SHARED)
#define PTHREAD_PROCESS_PRIVATE 0
#define PTHREAD_PROCESS_SHARED  1
#endif

#if defined(_POSIX_THREAD_PRIO_PROTECT)
#define PTHREAD_PRIO_NONE    0
#define PTHREAD_PRIO_INHERIT 1
#define PTHREAD_PRIO_PROTECT 2
#endif

#define PTHREAD_MUTEX_NORMAL     0
#define PTHREAD_MUTEX_RECURSIVE  1
#define PTHREAD_MUTEX_ERRORCHECK 2
#define PTHREAD_MUTEX_DEFAULT    PTHREAD_MUTEX_ERRORCHECK

typedef struct
{
  int       is_initialized;
  int       type;
  clockid_t clock_id;
} pthread_mutexattr_t;

typedef pthread_mutexattr_t pthread_rwlockattr_t;

#define _PTHREAD_MUTEX_INITIALIZER                  ((pthread_mutex_t)INVALID_HANDLE - 1)
#define _PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP     ((pthread_mutex_t)INVALID_HANDLE - 2)
#define _PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP    ((pthread_mutex_t)INVALID_HANDLE - 3)
#define _PTHREAD_MUTEX_INITIALIZER_MIN              ((pthread_mutex_t)INVALID_HANDLE - 3)
#define _PTHREAD_MUTEX_INITIALIZER_MAX              ((pthread_mutex_t)INVALID_HANDLE - 1)
#define _PTHREAD_MUTEX_INITING                      ((pthread_mutex_t)INVALID_HANDLE - 4)
#define _PTHREAD_RWLOCK_INITIALIZER                 _PTHREAD_MUTEX_INITIALIZER


#define _PTHREAD_COND_INITIALIZER   ((pthread_cond_t)INVALID_HANDLE - 1)
#define _PTHREAD_COND_INITING       ((pthread_cond_t)INVALID_HANDLE - 2)

typedef struct
{
  int       is_initialized;
  clockid_t clock;
} pthread_condattr_t;


#define _PTHREAD_ONCE_INIT  0


#endif /* ! _SYS__PTHREADTYPES_H_ */

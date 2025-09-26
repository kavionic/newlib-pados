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

#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <sys/cdefs.h>
#include <sys/lock.h>
#include <sys/_types.h>
#include <sys/_timespec.h>
#include <sys/pados_types.h>

typedef sem_id sem_t;

#define	SEM_FAILED	((sem_t*)0)

__BEGIN_DECLS
int	    sem_init(sem_t* semaphore, int shared, unsigned int count);
int	    sem_destroy(sem_t* semaphore);
sem_t*  sem_open(const char* name, int oflag, ...);
int	    sem_close(sem_t* semaphore);
int	    sem_unlink(const char* name);
int	    sem_getvalue(sem_t* semaphore, int* outCount);
int	    sem_wait(sem_t* semaphore);
int	    sem_trywait(sem_t* semaphore);
int	    sem_timedwait(sem_t* semaphore, const struct timespec* abstime);
int     sem_clockwait(sem_t* semaphore, __clockid_t clockID, const struct timespec* abstime);
int	    sem_post(sem_t* semaphore);
__END_DECLS

#endif /* _SEMAPHORE_H_ */

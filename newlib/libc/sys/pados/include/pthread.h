/* 
 * POSIX Threads API for PadOS
 * 
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

#ifndef PADOS_PTHREAD_H
#define PADOS_PTHREAD_H

#include <sys/types.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>
#include <sched.h>

#ifdef __cplusplus
extern "C" {
#endif


#define PTHREAD_ONCE_INIT _PTHREAD_ONCE_INIT

#define PTHREAD_BARRIER_SERIAL_THREAD  0x12345
#ifndef PTHREAD_CANCELED
#  define PTHREAD_CANCELED ((void*)-1)
#endif

#define PTHREAD_CANCEL_ENABLE    0
#define PTHREAD_CANCEL_DISABLE   1
#define PTHREAD_CANCEL_DEFERRED      0
#define PTHREAD_CANCEL_ASYNCHRONOUS  1

#define PTHREAD_MUTEX_RECURSIVE  2

#define PTHREAD_MUTEX_STALLED    0
#define PTHREAD_MUTEX_ROBUST     1

#ifndef CLOCK_REALTIME
#  define CLOCK_REALTIME 0
#endif

#define PTHREAD_MUTEX_INITIALIZER   _PTHREAD_MUTEX_INITIALIZER
#define PTHREAD_COND_INITIALIZER    _PTHREAD_COND_INITIALIZER
#define PTHREAD_RWLOCK_INITIALIZER  _PTHREAD_RWLOCK_INITIALIZER

//#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP  { .handle=NULL, .type=PTHREAD_MUTEX_RECURSIVE, .robust=PTHREAD_MUTEX_STALLED, .protocol=PTHREAD_PRIO_NONE, .pshared=PTHREAD_PROCESS_PRIVATE, .prioceiling=0 }
//#define PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP { .handle=NULL, .type=PTHREAD_MUTEX_ERRORCHECK, .robust=PTHREAD_MUTEX_STALLED, .protocol=PTHREAD_PRIO_NONE, .pshared=PTHREAD_PROCESS_PRIVATE, .prioceiling=0 }


 /* ===== Function pointer type for thread start routines ===== */
typedef void* (*pthread_start_routine)(void*);

/* ===== Core thread management ===== */
int   pthread_create(pthread_t* thread, const pthread_attr_t* attr, pthread_start_routine start_routine, void* arg);
void  pthread_exit(void* retval);
int   pthread_join(pthread_t thread, void** retval);
int   pthread_detach(pthread_t thread);

pthread_t pthread_self(void);
int   pthread_equal(pthread_t t1, pthread_t t2);

int   pthread_kill(pthread_t thread, int sig);

/* ===== Scheduling control (policy in <sched.h>) ===== */
int   pthread_getschedparam(pthread_t thread, int* policy,
    struct sched_param* param);
int   pthread_setschedparam(pthread_t thread, int policy,
    const struct sched_param* param);
int   pthread_setschedprio(pthread_t thread, int prio);

int   pthread_getconcurrency(void);
int   pthread_setconcurrency(int level);

/* ===== Thread attributes ===== */
int   pthread_attr_init(pthread_attr_t* attr);
int   pthread_attr_destroy(pthread_attr_t* attr);

int   pthread_attr_setdetachstate(pthread_attr_t* attr, int detachstate);
int   pthread_attr_getdetachstate(const pthread_attr_t* attr, int* detachstate);

int   pthread_attr_setinheritsched(pthread_attr_t* attr, int inheritsched);
int   pthread_attr_getinheritsched(const pthread_attr_t* attr, int* inheritsched);

int   pthread_attr_setschedpolicy(pthread_attr_t* attr, int policy);
int   pthread_attr_getschedpolicy(const pthread_attr_t* attr, int* policy);

int   pthread_attr_setschedparam(pthread_attr_t* attr,
    const struct sched_param* param);
int   pthread_attr_getschedparam(const pthread_attr_t* attr,
    struct sched_param* param);

int   pthread_attr_setscope(pthread_attr_t* attr, int scope);
int   pthread_attr_getscope(const pthread_attr_t* attr, int* scope);

int   pthread_attr_setstacksize(pthread_attr_t* attr, size_t stacksize);
int   pthread_attr_getstacksize(const pthread_attr_t* attr, size_t* stacksize);

int   pthread_attr_setstack(pthread_attr_t* attr, void* stackaddr, size_t stacksize);
int   pthread_attr_getstack(const pthread_attr_t* attr, void** stackaddr, size_t* stacksize);

int   pthread_attr_setguardsize(pthread_attr_t* attr, size_t guardsize);
int   pthread_attr_getguardsize(const pthread_attr_t* attr, size_t* guardsize);

/* ===== Cancellation ===== */
int   pthread_cancel(pthread_t thread);
void  pthread_testcancel(void);
int   pthread_setcancelstate(int state, int* oldstate);
int   pthread_setcanceltype(int type, int* oldtype);

/* ===== One-time initialization ===== */
int   pthread_once(pthread_once_t* once_control, void (*init_routine)(void));

/* ===== Thread-specific data (TLS keys) ===== */
int   pthread_key_create(pthread_key_t* key, void (*destructor)(void*));
int   pthread_key_delete(pthread_key_t key);
int   pthread_setspecific(pthread_key_t key, const void* value);
void* pthread_getspecific(pthread_key_t key);

/* ===== Mutexes ===== */
int   pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr);
int   pthread_mutex_destroy(pthread_mutex_t* mutex);
int   pthread_mutex_lock(pthread_mutex_t* mutex);
int   pthread_mutex_trylock(pthread_mutex_t* mutex);
int   pthread_mutex_timedlock(pthread_mutex_t* mutex, const struct timespec* abstime);
int   pthread_mutex_unlock(pthread_mutex_t* mutex);

/* Mutex attributes */
int   pthread_mutexattr_init(pthread_mutexattr_t* attr);
int   pthread_mutexattr_destroy(pthread_mutexattr_t* attr);

int   pthread_mutexattr_settype(pthread_mutexattr_t* attr, int type);
int   pthread_mutexattr_gettype(const pthread_mutexattr_t* attr, int* type);

int   pthread_mutexattr_setprotocol(pthread_mutexattr_t* attr, int protocol);
int   pthread_mutexattr_getprotocol(const pthread_mutexattr_t* attr, int* protocol);

int   pthread_mutexattr_setprioceiling(pthread_mutexattr_t* attr, int prioceiling);
int   pthread_mutexattr_getprioceiling(const pthread_mutexattr_t* attr, int* prioceiling);

int   pthread_mutexattr_setrobust(pthread_mutexattr_t* attr, int robust);
int   pthread_mutexattr_getrobust(const pthread_mutexattr_t* attr, int* robust);

int   pthread_mutexattr_setpshared(pthread_mutexattr_t* attr, int pshared);
int   pthread_mutexattr_getpshared(const pthread_mutexattr_t* attr, int* pshared);

/* Robust mutex owner-death handling (optional; define as stubs if not supported) */
int   pthread_mutex_consistent(pthread_mutex_t* mutex);

/* ===== Condition variables ===== */
int   pthread_cond_init(pthread_cond_t* cond, const pthread_condattr_t* attr);
int   pthread_cond_destroy(pthread_cond_t* cond);
int   pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mutex);
int   pthread_cond_timedwait(pthread_cond_t* cond, pthread_mutex_t* mutex,
    const struct timespec* abstime);
int   pthread_cond_signal(pthread_cond_t* cond);
int   pthread_cond_broadcast(pthread_cond_t* cond);

/* Condition attributes */
int   pthread_condattr_init(pthread_condattr_t* attr);
int   pthread_condattr_destroy(pthread_condattr_t* attr);

int   pthread_condattr_setpshared(pthread_condattr_t* attr, int pshared);
int   pthread_condattr_getpshared(const pthread_condattr_t* attr, int* pshared);

int   pthread_condattr_setclock(pthread_condattr_t* attr, clockid_t clock_id);
int   pthread_condattr_getclock(const pthread_condattr_t* attr, clockid_t* clock_id);

#if defined(_POSIX_READER_WRITER_LOCKS)
/* ===== Read-write locks ===== */
int   pthread_rwlock_init(pthread_rwlock_t* rwlock, const pthread_rwlockattr_t* attr);
int   pthread_rwlock_destroy(pthread_rwlock_t* rwlock);
int   pthread_rwlock_rdlock(pthread_rwlock_t* rwlock);
int   pthread_rwlock_tryrdlock(pthread_rwlock_t* rwlock);
int   pthread_rwlock_timedrdlock(pthread_rwlock_t* rwlock, const struct timespec* abstime);
int   pthread_rwlock_wrlock(pthread_rwlock_t* rwlock);
int   pthread_rwlock_trywrlock(pthread_rwlock_t* rwlock);
int   pthread_rwlock_timedwrlock(pthread_rwlock_t* rwlock, const struct timespec* abstime);
int   pthread_rwlock_unlock(pthread_rwlock_t* rwlock);

/* RWLock attributes */
int   pthread_rwlockattr_init(pthread_rwlockattr_t* attr);
int   pthread_rwlockattr_destroy(pthread_rwlockattr_t* attr);
int   pthread_rwlockattr_setpshared(pthread_rwlockattr_t* attr, int pshared);
int   pthread_rwlockattr_getpshared(const pthread_rwlockattr_t* attr, int* pshared);
#endif /* defined(_POSIX_READER_WRITER_LOCKS) */

#if defined(_POSIX_SPIN_LOCKS)
/* ===== Spin locks (may be mapped to fast mutex/IRQ-safe impl) ===== */
int   pthread_spin_init(pthread_spinlock_t* lock, int pshared);
int   pthread_spin_destroy(pthread_spinlock_t* lock);
int   pthread_spin_lock(pthread_spinlock_t* lock);
int   pthread_spin_trylock(pthread_spinlock_t* lock);
int   pthread_spin_unlock(pthread_spinlock_t* lock);
#endif /* defined(_POSIX_SPIN_LOCKS) */

#if defined(_POSIX_BARRIERS)
/* ===== Barriers ===== */
int   pthread_barrier_init(pthread_barrier_t* barrier,
    const pthread_barrierattr_t* attr,
    unsigned count);
int   pthread_barrier_destroy(pthread_barrier_t* barrier);
int   pthread_barrier_wait(pthread_barrier_t* barrier);

/* Barrier attributes */
int   pthread_barrierattr_init(pthread_barrierattr_t* attr);
int   pthread_barrierattr_destroy(pthread_barrierattr_t* attr);
int   pthread_barrierattr_setpshared(pthread_barrierattr_t* attr, int pshared);
int   pthread_barrierattr_getpshared(const pthread_barrierattr_t* attr, int* pshared);
#endif /* defined(_POSIX_BARRIERS) */

/* ===== Process-wide atfork handlers ===== */
int   pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void));

/* ===== CPU-time clock for a thread ===== */
int   pthread_getcpuclockid(pthread_t thread, clockid_t* clock_id);

//int   pthread_yield(void); /* May map to sched_yield() */


#ifdef __cplusplus
}
#endif

#endif /* PADOS_PTHREAD_H */

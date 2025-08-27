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

#include <pthread.h>

int   pthread_create(pthread_t* thread, const pthread_attr_t* attr, pthread_start_routine start_routine, void* arg)
{
    return -1;
}

void  pthread_exit(void* retval)
{
}

int   pthread_join(pthread_t thread, void** retval)
{
    return -1;
}

int   pthread_detach(pthread_t thread)
{
    return -1;
}

pthread_t pthread_self(void)
{
    return -1;
}

int   pthread_equal(pthread_t t1, pthread_t t2)
{
    return t1 == t2;
}


int   pthread_kill(pthread_t thread, int sig)
{
    return -1;
}

int   pthread_getschedparam(pthread_t thread, int* policy, struct sched_param* param)
{
    return -1;
}

int   pthread_setschedparam(pthread_t thread, int policy, const struct sched_param* param)
{
    return -1;
}

int   pthread_setschedprio(pthread_t thread, int prio)
{
    return -1;
}

int   pthread_getconcurrency(void)
{
    return -1;
}

int   pthread_setconcurrency(int level)
{
    return -1;
}

int   pthread_attr_init(pthread_attr_t* attr)
{
    return -1;
}

int   pthread_attr_destroy(pthread_attr_t* attr)
{
    return -1;
}

int   pthread_attr_setdetachstate(pthread_attr_t* attr, int detachstate)
{
    return -1;
}

int   pthread_attr_getdetachstate(const pthread_attr_t* attr, int* detachstate)
{
    return -1;
}

int   pthread_attr_setinheritsched(pthread_attr_t* attr, int inheritsched)
{
    return -1;
}

int   pthread_attr_getinheritsched(const pthread_attr_t* attr, int* inheritsched)
{
    return -1;
}


int   pthread_attr_setschedpolicy(pthread_attr_t* attr, int policy)
{
    return -1;
}

int   pthread_attr_getschedpolicy(const pthread_attr_t* attr, int* policy)
{
    return -1;
}

int   pthread_attr_setschedparam(pthread_attr_t* attr, const struct sched_param* param)
{
    return -1;
}

int   pthread_attr_getschedparam(const pthread_attr_t* attr, struct sched_param* param)
{
    return -1;
}

int   pthread_attr_setscope(pthread_attr_t* attr, int scope)
{
    return -1;
}

int   pthread_attr_getscope(const pthread_attr_t* attr, int* scope)
{
    return -1;
}

int   pthread_attr_setstacksize(pthread_attr_t* attr, size_t stacksize)
{
    return -1;
}

int   pthread_attr_getstacksize(const pthread_attr_t* attr, size_t* stacksize)
{
    return -1;
}

int   pthread_attr_setstack(pthread_attr_t* attr, void* stackaddr, size_t stacksize)
{
    return -1;
}

int   pthread_attr_getstack(const pthread_attr_t* attr, void** stackaddr, size_t* stacksize)
{
    return -1;
}

int   pthread_attr_setguardsize(pthread_attr_t* attr, size_t guardsize)
{
    return -1;
}

int   pthread_attr_getguardsize(const pthread_attr_t* attr, size_t* guardsize)
{
    return -1;
}

int   pthread_cancel(pthread_t thread)
{
    return -1;
}

void  pthread_testcancel(void)
{
}

int   pthread_setcancelstate(int state, int* oldstate)
{
    return -1;
}

int   pthread_setcanceltype(int type, int* oldtype)
{
    return -1;
}

int   pthread_once(pthread_once_t* once_control, void (*init_routine)(void))
{
    return -1;
}

int   pthread_key_create(pthread_key_t* key, void (*destructor)(void*))
{
    return -1;
}

int   pthread_key_delete(pthread_key_t key)
{
    return -1;
}

int   pthread_setspecific(pthread_key_t key, const void* value)
{
    return -1;
}

void* pthread_getspecific(pthread_key_t key)
{
    return 0;
}

int   pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr)
{
    return -1;
}

int   pthread_mutex_destroy(pthread_mutex_t* mutex)
{
    return -1;
}

int   pthread_mutex_lock(pthread_mutex_t* mutex)
{
    return -1;
}

int   pthread_mutex_trylock(pthread_mutex_t* mutex)
{
    return -1;
}

int   pthread_mutex_timedlock(pthread_mutex_t* mutex, const struct timespec* abstime)
{
    return -1;
}

int   pthread_mutex_unlock(pthread_mutex_t* mutex)
{
    return -1;
}

int   pthread_mutexattr_init(pthread_mutexattr_t* attr)
{
    return -1;
}

int   pthread_mutexattr_destroy(pthread_mutexattr_t* attr)
{
    return -1;
}

int   pthread_mutexattr_settype(pthread_mutexattr_t* attr, int type)
{
    return -1;
}

int   pthread_mutexattr_gettype(const pthread_mutexattr_t* attr, int* type)
{
    return -1;
}

int   pthread_mutexattr_setprotocol(pthread_mutexattr_t* attr, int protocol)
{
    return -1;
}

int   pthread_mutexattr_getprotocol(const pthread_mutexattr_t* attr, int* protocol)
{
    return -1;
}

int   pthread_mutexattr_setprioceiling(pthread_mutexattr_t* attr, int prioceiling)
{
    return -1;
}

int   pthread_mutexattr_getprioceiling(const pthread_mutexattr_t* attr, int* prioceiling)
{
    return -1;
}

int   pthread_mutexattr_setrobust(pthread_mutexattr_t* attr, int robust)
{
    return -1;
}

int   pthread_mutexattr_getrobust(const pthread_mutexattr_t* attr, int* robust)
{
    return -1;
}

int   pthread_mutexattr_setpshared(pthread_mutexattr_t* attr, int pshared)
{
    return -1;
}

int   pthread_mutexattr_getpshared(const pthread_mutexattr_t* attr, int* pshared)
{
    return -1;
}

int   pthread_mutex_consistent(pthread_mutex_t* mutex)
{
    return -1;
}

int   pthread_cond_init(pthread_cond_t* cond, const pthread_condattr_t* attr)
{
    return -1;
}

int   pthread_cond_destroy(pthread_cond_t* cond)
{
    return -1;
}

int   pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mutex)
{
    return -1;
}

int   pthread_cond_timedwait(pthread_cond_t* cond, pthread_mutex_t* mutex, const struct timespec* abstime)
{
    return -1;
}

int   pthread_cond_signal(pthread_cond_t* cond)
{
    return -1;
}

int   pthread_cond_broadcast(pthread_cond_t* cond)
{
    return -1;
}

int   pthread_condattr_init(pthread_condattr_t* attr)
{
    return -1;
}

int   pthread_condattr_destroy(pthread_condattr_t* attr)
{
    return -1;
}

int   pthread_condattr_setpshared(pthread_condattr_t* attr, int pshared)
{
    return -1;
}

int   pthread_condattr_getpshared(const pthread_condattr_t* attr, int* pshared)
{
    return -1;
}

int   pthread_condattr_setclock(pthread_condattr_t* attr, clockid_t clock_id)
{
    return -1;
}

int   pthread_condattr_getclock(const pthread_condattr_t* attr, clockid_t* clock_id)
{
    return -1;
}

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

int   pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void))
{
    return -1;
}

int   pthread_getcpuclockid(pthread_t thread, clockid_t* clock_id)
{
    return -1;
}

//int   pthread_yield(void)
//{
//    return -1;
//}


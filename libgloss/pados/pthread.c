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

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <sys/cdefs.h>
#include <sys/pados_timeutils.h>
#include <sys/pados_syscalls.h>
#include <pthread.h>


static pthread_mutex_t g_pthread_once_mutex = _PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  g_pthread_once_cond = _PTHREAD_COND_INITIALIZER;

static inline pthread_mutex_t lazy_mutex_init(pthread_mutex_t* mutex)
{
    for (;;)
    {
        pthread_mutex_t prevHandle = atomic_load_explicit(mutex, memory_order_acquire);
        pthread_mutex_t handle = prevHandle;

        if (handle >= _PTHREAD_MUTEX_INITIALIZER_MIN && handle <= _PTHREAD_MUTEX_INITIALIZER_MAX)
        {
            if (atomic_compare_exchange_strong_explicit(mutex, &handle, _PTHREAD_MUTEX_INITING, memory_order_acq_rel, memory_order_acquire))
            {
                int result;
                if (prevHandle == _PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP)
                {
                    pthread_mutexattr_t attr;
                    result = pthread_mutexattr_init(&attr);
                    if (result == 0)
                    {
                        result = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
                        if (result == 0)
                        {
                            result = pthread_mutex_init(&handle, &attr);
                        }
                    }
                }
                else if (prevHandle == _PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP)
                {
                    pthread_mutexattr_t attr;
                    result = pthread_mutexattr_init(&attr);
                    if (result == 0)
                    {
                        result = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
                        if (result == 0)
                        {
                            result = pthread_mutex_init(&handle, &attr);
                        }
                    }
                }
                else
                {
                    result = pthread_mutex_init(&handle, NULL);
                }
                if (result != 0)
                {
                    atomic_store_explicit(mutex, prevHandle, memory_order_release);
                    return INVALID_HANDLE;
                }
                atomic_store_explicit(mutex, handle, memory_order_release);
                return handle;
            }
            continue;
        }
        if (handle == _PTHREAD_MUTEX_INITING)
        {
            do
            {
                __yield();
                handle = atomic_load_explicit(mutex, memory_order_acquire);
            } while (handle == _PTHREAD_MUTEX_INITING);
            if (handle != prevHandle) return handle;
            continue;
        }
        return handle;
    }
}

static inline pthread_mutex_t get_mutex_handle(pthread_mutex_t* mutex)
{
    pthread_mutex_t handle = atomic_load_explicit(mutex, memory_order_acquire);
    if (__builtin_expect((handle >= _PTHREAD_MUTEX_INITIALIZER_MIN && handle <= _PTHREAD_MUTEX_INITIALIZER_MAX) || handle == _PTHREAD_MUTEX_INITING, 0)) {
        handle = lazy_mutex_init(mutex);
    }
    return handle;
}

static inline pthread_cond_t lazy_cond_init(pthread_cond_t* cond)
{
    for (;;)
    {
        pthread_cond_t handle = atomic_load_explicit(cond, memory_order_acquire);

        if (handle == _PTHREAD_COND_INITIALIZER)
        {
            if (atomic_compare_exchange_strong_explicit(cond, &handle, _PTHREAD_COND_INITING, memory_order_acq_rel, memory_order_acquire))
            {
                if (pthread_cond_init(&handle, NULL) != 0)
                {
                    atomic_store_explicit(cond, _PTHREAD_COND_INITIALIZER, memory_order_release);
                    return INVALID_HANDLE;
                }
                atomic_store_explicit(cond, handle, memory_order_release);
                return handle;
            }
            continue;
        }
        if (handle == _PTHREAD_COND_INITING)
        {
            do
            {
                __yield();
                handle = atomic_load_explicit(cond, memory_order_acquire);
            } while (handle == _PTHREAD_COND_INITING);
            if (handle != _PTHREAD_COND_INITIALIZER) return handle;
            continue;
        }
        return handle;
    }
}

static inline pthread_cond_t get_cond_handle(pthread_cond_t* cond)
{
    pthread_cond_t handle = atomic_load_explicit(cond, memory_order_acquire);
    if (__builtin_expect(handle == _PTHREAD_COND_INITIALIZER || handle == _PTHREAD_COND_INITING, 0)) {
        handle = lazy_cond_init(cond);
    }
    return handle;
}

int pthread_create(pthread_t* thread, const pthread_attr_t* attr, pthread_start_routine start_routine, void* arg)
{
    PThreadAttribs nativeAttribs;

    __thread_attribs_init(&nativeAttribs);

    nativeAttribs.Name = "pthread";
    nativeAttribs.DetachState = PThreadDetachState_Joinable;

    if (attr != NULL)
    {
        nativeAttribs.DetachState   = (attr->detachstate == PTHREAD_CREATE_JOINABLE) ? PThreadDetachState_Joinable : PThreadDetachState_Detached;
        nativeAttribs.Priority      = attr->schedparam.sched_priority;
        nativeAttribs.StackAddress  = attr->stackaddr;
        nativeAttribs.StackSize     = attr->stacksize;
    }
    return __thread_spawn(thread, &nativeAttribs, start_routine, arg);
}

void pthread_exit(void* retval)
{
    __thread_exit(retval);
}

int pthread_join(pthread_t thread, void** retval)
{
    return __thread_join(thread, retval);
}

int pthread_detach(pthread_t thread)
{
    return __thread_detach(thread);
}

pthread_t pthread_self(void)
{
    return __get_thread_id();
}

int pthread_equal(pthread_t t1, pthread_t t2)
{
    return t1 == t2;
}

int pthread_kill(pthread_t thread, int sig)
{
    return __thread_kill(thread, sig);
}

int pthread_getschedparam(pthread_t thread, int* policy, struct sched_param* param)
{
    int priority;
    int result = __thread_get_priority(thread, &priority);
    if (result == 0)
    {
        *policy = SCHED_RR;
        param->sched_priority = priority;
    }
    return result;
}

int pthread_setschedparam(pthread_t thread, int policy, const struct sched_param* param)
{
    return __thread_set_priority(thread, param->sched_priority);
}

int pthread_setschedprio(pthread_t thread, int priority)
{
    return __thread_set_priority(thread, priority);
}

static int g_dummy_pthread_concurrency = 0;

int pthread_getconcurrency(void)
{
    return g_dummy_pthread_concurrency;
}

int pthread_setconcurrency(int level)
{
    g_dummy_pthread_concurrency = level;
    return 0;
}

int pthread_attr_init(pthread_attr_t* attr)
{
    memset(attr, 0, sizeof(*attr));
    attr->is_initialized = true;
    attr->detachstate = PTHREAD_CREATE_JOINABLE;
    return 0;
}

int pthread_attr_destroy(pthread_attr_t* attr)
{
    attr->is_initialized = false;
    return 0;
}

int pthread_attr_setdetachstate(pthread_attr_t* attr, int detachstate)
{
    attr->detachstate = detachstate;
    return 0;
}

int pthread_attr_getdetachstate(const pthread_attr_t* attr, int* detachstate)
{
    *detachstate = attr->detachstate;
    return 0;
}

int pthread_attr_setinheritsched(pthread_attr_t* attr, int inheritsched)
{
    attr->inheritsched = inheritsched;
    return 0;
}

int pthread_attr_getinheritsched(const pthread_attr_t* attr, int* inheritsched)
{
    *inheritsched = attr->inheritsched;
    return 0;
}


int pthread_attr_setschedpolicy(pthread_attr_t* attr, int policy)
{
    attr->schedpolicy = policy;
    return 0;
}

int pthread_attr_getschedpolicy(const pthread_attr_t* attr, int* policy)
{
    *policy = attr->schedpolicy;
    return 0;
}

int pthread_attr_setschedparam(pthread_attr_t* attr, const struct sched_param* param)
{
    attr->schedparam = *param;
    return 0;
}

int pthread_attr_getschedparam(const pthread_attr_t* attr, struct sched_param* param)
{
    *param = attr->schedparam;
    return 0;
}

int pthread_attr_setscope(pthread_attr_t* attr, int scope)
{
    attr->contentionscope = scope;
    return 0;
}

int pthread_attr_getscope(const pthread_attr_t* attr, int* scope)
{
    *scope = attr->contentionscope;
    return 0;
}

int pthread_attr_setstacksize(pthread_attr_t* attr, size_t stacksize)
{
    attr->stacksize = stacksize;
    return 0;
}

int pthread_attr_getstacksize(const pthread_attr_t* attr, size_t* stacksize)
{
    *stacksize = attr->stacksize;
    return 0;
}

int pthread_attr_setstack(pthread_attr_t* attr, void* stackaddr, size_t stacksize)
{
    attr->stackaddr = stackaddr;
    attr->stacksize = stacksize;
    return 0;
}

int pthread_attr_getstack(const pthread_attr_t* attr, void** stackaddr, size_t* stacksize)
{
    *stackaddr = attr->stackaddr;
    *stacksize = attr->stacksize;
    return 0;
}

int pthread_attr_setguardsize(pthread_attr_t* attr, size_t guardsize)
{
    attr->guardsize = guardsize;
    return 0;
}

int pthread_attr_getguardsize(const pthread_attr_t* attr, size_t* guardsize)
{
    *guardsize = attr->guardsize;
    return 0;
}

int pthread_cancel(pthread_t thread)
{
    return ENOSYS;
}

void pthread_testcancel(void)
{
}

_Thread_local int gt_dummy_pthread_cancelstate = PTHREAD_CANCEL_ENABLE;
int pthread_setcancelstate(int state, int* oldstate)
{
    *oldstate = gt_dummy_pthread_cancelstate;
    gt_dummy_pthread_cancelstate = state;
    return 0;
}

_Thread_local int gt_dummy_pthread_canceltype = PTHREAD_CANCEL_DEFERRED;
int pthread_setcanceltype(int type, int* oldtype)
{
    *oldtype = gt_dummy_pthread_canceltype;
    gt_dummy_pthread_canceltype = type;
    return 0;
}

int pthread_once(pthread_once_t* once_control, void (*init_routine)(void))
{
    if (__builtin_expect(atomic_load_explicit(once_control, memory_order_acquire) == 2, 1)) {
        return 0;
    }
    int expected = 0;
    if (atomic_compare_exchange_strong_explicit(once_control, &expected, 1, memory_order_acq_rel, memory_order_acquire))
    {
        /* We won: invoke the initializer outside any locks */
        init_routine();

        /* Publish completion and then wake waiters under g_pthread_once_mutex to avoid lost wake ups */
        atomic_store_explicit(once_control, 2, memory_order_release);

        pthread_mutex_lock(&g_pthread_once_mutex);
        pthread_cond_broadcast(&g_pthread_once_cond);
        pthread_mutex_unlock(&g_pthread_once_mutex);
        return 0;
    }

    /* Another thread is (or was) initializing. Wait until state==2 under g_pthread_once_mutex. */
    pthread_mutex_lock(&g_pthread_once_mutex);
    while (atomic_load_explicit(once_control, memory_order_acquire) != 2) {
        pthread_cond_wait(&g_pthread_once_cond, &g_pthread_once_mutex);
    }
    pthread_mutex_unlock(&g_pthread_once_mutex);
    return 0;
}

int pthread_key_create(pthread_key_t* key, void (*destructor)(void*))
{
    pthread_key_t handle = __thread_local_create_key(destructor);
    if (handle < 0) {
        return errno;
    }
    *key = handle;
    return 0;
}

int pthread_key_delete(pthread_key_t key)
{
    return __thread_local_delete_key(key);
}

int pthread_setspecific(pthread_key_t key, const void* value)
{
    return __thread_local_set(key, value);
}

void* pthread_getspecific(pthread_key_t key)
{
    return __thread_local_get(key);
}

int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr)
{
    PEMutexRecursionMode mode = PEMutexRecursionMode_RaiseError;
    clockid_t clockID = CLOCK_REALTIME_COARSE;
    if (attr != NULL)
    {
        switch (attr->type)
        {
            case PTHREAD_MUTEX_NORMAL:      mode = PEMutexRecursionMode_Block; break;
            case PTHREAD_MUTEX_RECURSIVE:   mode = PEMutexRecursionMode_Recurse; break;
            case PTHREAD_MUTEX_ERRORCHECK:  mode = PEMutexRecursionMode_RaiseError; break;
            default:
                return EINVAL;
        }
        clockID = attr->clock_id;
    }
    pthread_mutex_t handle;
    const PErrorCode result = __mutex_create(&handle, "ptmtx", mode, clockID);

    if (result != PErrorCode_Success) {
        return result;
    }
    atomic_store_explicit(mutex, handle, memory_order_release);
    return PErrorCode_Success;
}

int pthread_mutex_destroy(pthread_mutex_t* mutex)
{
    return __mutex_delete(get_mutex_handle(mutex));
}

int pthread_mutex_lock(pthread_mutex_t* mutex)
{
    return __mutex_lock(get_mutex_handle(mutex));
}

int pthread_mutex_trylock(pthread_mutex_t* mutex)
{
    return __mutex_try_lock(get_mutex_handle(mutex));
}

int pthread_mutex_timedlock(pthread_mutex_t* mutex, const struct timespec* abstime)
{
    return __mutex_lock_deadline_ns(get_mutex_handle(mutex), timespec_to_nanos(abstime));
}

int pthread_mutex_clocklock(pthread_mutex_t* mutex, clockid_t clockID, const struct timespec* abstime)
{
    return __mutex_lock_clock_ns(get_mutex_handle(mutex), clockID, timespec_to_nanos(abstime));
}

int pthread_mutex_unlock(pthread_mutex_t* mutex)
{
    return __mutex_unlock(get_mutex_handle(mutex));
}

int pthread_mutexattr_init(pthread_mutexattr_t* attr)
{
    attr->is_initialized = true;
    attr->type = PTHREAD_MUTEX_DEFAULT;
    attr->clock_id = CLOCK_REALTIME_COARSE;
    return 0;
}

int pthread_mutexattr_destroy(pthread_mutexattr_t* attr)
{
    if (attr->is_initialized == true)
    {
        attr->is_initialized = 0;
        return 0;
    }
    return EINVAL;
}

int pthread_mutexattr_settype(pthread_mutexattr_t* attr, int type)
{
    if (attr->is_initialized == true)
    {
        attr->type = type;
        return 0;
    }
    return EINVAL;
}

int pthread_mutexattr_gettype(const pthread_mutexattr_t* attr, int* type)
{
    if (attr->is_initialized == true)
    {
        *type = attr->type;
        return 0;
    }
    return EINVAL;
}

int pthread_mutexattr_getclock(const pthread_mutexattr_t* attr, clockid_t* clockID)
{
    if (attr->is_initialized == true)
    {
        *clockID = attr->clock_id;
        return 0;
    }
    return EINVAL;
}

int pthread_mutexattr_setclock(pthread_mutexattr_t* attr, clockid_t clockID)
{
    if (attr->is_initialized == true)
    {
        attr->clock_id = clockID;
        return 0;
    }
    return EINVAL;
}

int pthread_cond_init(pthread_cond_t* cond, const pthread_condattr_t* attr)
{
    int clockID = CLOCK_REALTIME;
    if (attr != NULL)
    {
        if (!attr->is_initialized)
        {
            return PErrorCode_InvalidArg;
        }
        clockID = attr->clock;
    }
    handle_id handle;
    const PErrorCode result = __condition_var_create(&handle, "ptcnd", clockID);

    if (result != PErrorCode_Success) {
        return result;
    }
    atomic_store_explicit(cond, handle, memory_order_release);
    return PErrorCode_Success;
}

int pthread_cond_destroy(pthread_cond_t* cond)
{
    return __condition_var_delete(get_cond_handle(cond));
}

int pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mutex)
{
    return __condition_var_wait(get_cond_handle(cond), get_mutex_handle(mutex));
}

int pthread_cond_timedwait(pthread_cond_t* cond, pthread_mutex_t* mutex, const struct timespec* abstime)
{
    return __condition_var_wait_deadline_ns(get_cond_handle(cond), get_mutex_handle(mutex), timespec_to_nanos(abstime));
}

int pthread_cond_clockwait(pthread_cond_t* cond, pthread_mutex_t* mutex, clockid_t clockID, const struct timespec* abstime)
{
    return __condition_var_wait_clock_ns(get_cond_handle(cond), get_mutex_handle(mutex), clockID, timespec_to_nanos(abstime));
}

int pthread_cond_signal(pthread_cond_t* cond)
{
    return __condition_var_wakeup(get_cond_handle(cond), 1);
}

int pthread_cond_broadcast(pthread_cond_t* cond)
{
    return __condition_var_wakeup_all(get_cond_handle(cond));
}

int pthread_condattr_init(pthread_condattr_t* attr)
{
    attr->is_initialized = true;
    attr->clock = CLOCK_REALTIME;
    return 0;
}

int pthread_condattr_destroy(pthread_condattr_t* attr)
{
    attr->is_initialized = 0;
    return 0;
}

int pthread_condattr_setclock(pthread_condattr_t* attr, clockid_t clock_id)
{
    attr->clock = clock_id;
    return 0;
}

int pthread_condattr_getclock(const pthread_condattr_t* attr, clockid_t* clock_id)
{
    *clock_id = attr->clock;
    return 0;
}

int pthread_rwlock_init(pthread_rwlock_t* rwlock, const pthread_rwlockattr_t* attr)
{
    pthread_rwlockattr_t defaultAttr;
    if (attr == NULL)
    {
        pthread_mutexattr_init(&defaultAttr);
        defaultAttr.type = PTHREAD_MUTEX_NORMAL;
        attr = &defaultAttr;
    }
    return pthread_mutex_init(rwlock, attr);
}
int pthread_rwlock_destroy(pthread_rwlock_t* rwlock)
{
    return pthread_mutex_destroy(rwlock);
}

int pthread_rwlock_rdlock(pthread_rwlock_t* rwlock)
{
    return __mutex_lock_shared(get_mutex_handle(rwlock));
}

int pthread_rwlock_tryrdlock(pthread_rwlock_t* rwlock)
{
    return pthread_mutex_trylock(rwlock);
}

int pthread_rwlock_timedrdlock(pthread_rwlock_t* rwlock, const struct timespec* abstime)
{
    return pthread_mutex_timedlock(rwlock, abstime);
}

int pthread_rwlock_wrlock(pthread_rwlock_t* rwlock)
{
    return pthread_mutex_lock(rwlock);
}

int pthread_rwlock_trywrlock(pthread_rwlock_t* rwlock)
{
    return pthread_mutex_trylock(rwlock);
}

int pthread_rwlock_timedwrlock(pthread_rwlock_t* rwlock, const struct timespec* abstime)
{
    return pthread_mutex_timedlock(rwlock, abstime);
}

int pthread_rwlock_unlock(pthread_rwlock_t* rwlock)
{
    return pthread_mutex_unlock(rwlock);
}

int pthread_rwlockattr_init(pthread_rwlockattr_t* attr)
{
    int result = pthread_mutexattr_init(attr);
    if (result == 0) {
        attr->type = PTHREAD_MUTEX_NORMAL;
    }
    return result;
}

int pthread_rwlockattr_destroy(pthread_rwlockattr_t* attr)
{
    return pthread_mutexattr_destroy(attr);
}

//int   pthread_rwlockattr_setpshared(pthread_rwlockattr_t* attr, int pshared);
//int   pthread_rwlockattr_getpshared(const pthread_rwlockattr_t* attr, int* pshared);


enum { SPIN_UNLOCKED = 0, SPIN_LOCKED = 1 };

int pthread_spin_init(pthread_spinlock_t* lock, int pshared)
{
    (void)pshared;
    atomic_store_explicit(lock, SPIN_UNLOCKED, memory_order_release);
    return 0;
}

int pthread_spin_destroy(pthread_spinlock_t* lock)
{
    atomic_int value = atomic_load_explicit(lock, memory_order_relaxed);
    
    if (value == SPIN_LOCKED) {
        return EBUSY;
    } else if (value != SPIN_UNLOCKED) {
        return EINVAL;
    } else {
        return 0;
    }
}

int pthread_spin_lock(pthread_spinlock_t* lock)
{
    for (;;)
    {
        int expected = SPIN_UNLOCKED;
        if (atomic_compare_exchange_strong_explicit(lock, &expected, SPIN_LOCKED, memory_order_acquire, memory_order_acquire)) {
            break;
        }
        while (atomic_load_explicit(lock, memory_order_relaxed) == SPIN_LOCKED)
        {
#if defined(__aarch64__) || defined(__arm__)
            __asm__ __volatile__("yield");
#endif
        }
    }
    return 0;
}

int pthread_spin_trylock(pthread_spinlock_t* lock)
{
    int expected = SPIN_UNLOCKED;
    return atomic_compare_exchange_strong_explicit(lock, &expected, SPIN_LOCKED, memory_order_acquire, memory_order_relaxed) ? 0 : EBUSY;
}

int pthread_spin_unlock(pthread_spinlock_t* lock)
{
    atomic_store_explicit(lock, SPIN_UNLOCKED, memory_order_release);
    return 0;
}

int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void))
{
    return ENOSYS;
}

int pthread_getcpuclockid(pthread_t thread, clockid_t* clock_id)
{
    *clock_id = THREADID_TO_CLOCKID(thread);
    return 0;
}

int pthread_yield(void)
{
    return __yield();
}

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

#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/pados_types.h>
#include <sys/pados_error_codes.h>
#include <sys/pados_threads.h>
#include <sys/pados_mutex.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*TLSDestructor_t)(void*);

/*
 * IO functions
 */

int sys_open(const char* path, int flags);
int sys_close(int file);
int sys_dup(int oldFile);
int sys_dup2(int oldFile, int newFile);
int sys_rename(const char* oldPath, const char* newPath);
int sys_fstat(int file, struct stat* buf);
int sys_stat(const char* path, struct stat* buf);
int sys_isatty(int file);
off64_t sys_lseek(int file, off64_t offset, int whence);
ssize_t sys_read(int file, void* buffer, size_t length);
ssize_t sys_write(int file, const void* buffer, size_t length);
int sys_create_directory(const char* name, mode_t permission);
int sys_create_directory_base(int baseFolderFD, const char* name, int permission);
int sys_unlink(const char* path);

/*
 * Time functions
 */

bigtime_t sys_get_system_time();
bigtime_t sys_get_system_time_hires();
bigtime_t sys_get_real_time();
status_t  sys_set_real_time(bigtime_t time, bool updateRTC);
bigtime_t sys_get_clock_time_offset(clockid_t clockID);
bigtime_t sys_get_clock_time(clockid_t clockID);
bigtime_t sys_get_clock_time_hires(clockid_t clockID);
status_t  sys_get_clock_resolution(clockid_t clockID, bigtime_t* outResolutionNanos);
status_t  sys_set_clock_resolution(clockid_t clockID, bigtime_t resolutionNanos);

/*
 * Thread functions
 */

int         sys_thread_attribs_init(PThreadAttribs* attribs);
PErrorCode  sys_thread_spawn(thread_id* outHandle, const PThreadAttribs* attribs, ThreadEntryPoint_t entryPoint, void* arguments);
void        sys_thread_exit(void* returnValue);
int         sys_thread_detach(thread_id handle);
int         sys_thread_join(thread_id handle, void** outReturnValue);
thread_id   sys_get_thread_id();
int         sys_thread_set_priority(thread_id handle, int priority);
int         sys_thread_get_priority(thread_id handle, int* outPriority);
int         sys_get_thread_info(handle_id handle, ThreadInfo* info);
int         sys_get_next_thread_info(ThreadInfo* info);
status_t    sys_snooze_us(bigtime_t micros);
int         sys_yield();
PErrorCode  sys_thread_kill(pid_t pid, int sig);

/*
 * Process functions
 */

pid_t       sys_getpid(void);
PErrorCode  sys_kill(pid_t pid, int sig);
caddr_t     sys_sbrk(ptrdiff_t size);
void        sys_exit(int exitCode) _ATTRIBUTE((__noreturn__));
PErrorCode  sys_sysconf(int name, long* outValue);

/*
 * Mutex functions
 */

PErrorCode  sys_create_mutex(sem_id* outHandle, const char* name, PEMutexRecursionMode recursionMode, clockid_t clockID);
PErrorCode  sys_duplicate_mutex(sem_id* outNewHandle, sem_id handle);
status_t sys_delete_mutex(sem_id handle);
status_t sys_lock_mutex(sem_id handle);
status_t sys_lock_mutex_timeout(sem_id handle, bigtime_t timeout);
status_t sys_lock_mutex_deadline(sem_id handle, bigtime_t deadline);
status_t sys_lock_mutex_clock(sem_id handle, clockid_t clockID, bigtime_t deadline);
status_t sys_try_lock_mutex(sem_id handle);
status_t sys_unlock_mutex(sem_id handle);

status_t sys_lock_mutex_shared(sem_id handle);
status_t sys_lock_mutex_shared_timeout(sem_id handle, bigtime_t timeout);
status_t sys_lock_mutex_shared_deadline(sem_id handle, bigtime_t deadline);
status_t sys_try_lock_mutex_shared(sem_id handle);
status_t sys_unlock_mutex_shared(sem_id handle);
status_t sys_islocked_mutex(sem_id handle);

/*
 * Condition variable functions
 */

PErrorCode  sys_condition_var_create(handle_id* outHandle, const char* name, clockid_t clockID);
status_t    sys_condition_var_delete(handle_id handle);
status_t    sys_condition_var_wait(handle_id handle, handle_id mutexHandle);
status_t    sys_condition_var_wait_timeout(handle_id handle, handle_id mutexHandle, bigtime_t timeout);
status_t    sys_condition_var_wait_deadline(handle_id handle, handle_id mutexHandle, bigtime_t deadline);
status_t    sys_condition_var_wait_clock(handle_id handle, handle_id mutexHandle, clockid_t clockID, bigtime_t deadline);
status_t    sys_condition_var_wakeup(handle_id handle, int threadCount);
status_t    sys_condition_var_wakeup_all(handle_id handle);

/*
 * Thread local functions
 */

tls_id  sys_thread_local_create_key(TLSDestructor_t destructor);
int     sys_thread_local_delete_key(int tls_id);
int     sys_thread_local_set(tls_id slot, const void* value);
void*   sys_thread_local_get(tls_id slot);

#ifdef __cplusplus
}
#endif

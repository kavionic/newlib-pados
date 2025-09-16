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

#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include "sys/pados_syscalls.h"
#include <sched.h>


void* __attribute__((weak)) __aeabi_read_tp(void) { return NULL; }
//link_warning(__aeabi_read_tp, "__aeabi_read_tp is not implemented and will always fail");

/*
 * IO functions
 */

int     __attribute__((weak)) sys_open(const char* path, int flags) { return -1; }
int     __attribute__((weak)) sys_close(int file) { return -1; }
int     __attribute__((weak)) sys_dup(int oldFile) { return -1; }
int     __attribute__((weak)) sys_dup2(int oldFile, int newFile) { return -1; }
int     __attribute__((weak)) sys_rename(const char* oldPath, const char* newPath) { return -1; }
int     __attribute__((weak)) sys_fstat(int file, struct stat* buf) { return -1; }
int     __attribute__((weak)) sys_stat(const char* path, struct stat* buf) { return -1; }
int     __attribute__((weak)) sys_isatty(int file) { return -1; }
off64_t __attribute__((weak)) sys_lseek(int file, off64_t offset, int whence) { return -1; }
ssize_t __attribute__((weak)) sys_read(int file, void* buffer, size_t length) { return -1; }
ssize_t __attribute__((weak)) sys_write(int file, const void* buffer, size_t length) { return -1; }
int     __attribute__((weak)) sys_create_directory(const char* name, mode_t permission) { return -1; }
int     __attribute__((weak)) sys_create_directory_base(int baseFolderFD, const char* name, int permission) { return -1; }
int     __attribute__((weak)) sys_unlink(const char* path) { return -1; }

/*
 * Time functions
 */

bigtime_t __attribute__((weak)) sys_get_system_time() { return -1; }
bigtime_t __attribute__((weak)) sys_get_system_time_hires() { return -1; }
bigtime_t __attribute__((weak)) sys_get_real_time() { return -1; }
status_t  __attribute__((weak)) sys_set_real_time(bigtime_t time, bool updateRTC) { return -1; }
bigtime_t __attribute__((weak)) sys_get_clock_time_offset(int clockID) { return -1; }
bigtime_t __attribute__((weak)) sys_get_clock_time(int clockID) { return -1; }
bigtime_t __attribute__((weak)) sys_get_clock_time_hires(int clockID) { return -1; }
status_t  __attribute__((weak)) sys_get_clock_resolution(clockid_t clockID, bigtime_t* resolutionNanos) { return -1; }
status_t  __attribute__((weak)) sys_set_clock_resolution(clockid_t clockID, bigtime_t resolutionNanos) { return -1; }

/*
 * Thread functions
 */

int         __attribute__((weak)) sys_thread_attribs_init(PThreadAttribs* attribs) { return -1; }
PErrorCode  __attribute__((weak)) sys_thread_spawn(thread_id* outHandle, const PThreadAttribs* attribs, ThreadEntryPoint_t entryPoint, void* arguments) { return -1; }
void        __attribute__((weak)) sys_thread_exit(void* returnValue) {}
int         __attribute__((weak)) sys_thread_detach(thread_id handle) { return -1; }
int         __attribute__((weak)) sys_thread_join(thread_id handle, void** outReturnValue) { return -1; }
thread_id   __attribute__((weak)) sys_get_thread_id() { return -1; }
int         __attribute__((weak)) sys_thread_set_priority(thread_id handle, int priority) { return -1; }
int         __attribute__((weak)) sys_thread_get_priority(thread_id handle, int* outPriority) { return -1; }
int         __attribute__((weak)) sys_get_thread_info(handle_id handle, ThreadInfo* info) { return -1; }
int         __attribute__((weak)) sys_get_next_thread_info(ThreadInfo* info) { return -1; }
status_t    __attribute__((weak)) sys_snooze_us(bigtime_t micros) { return -1; }
int         __attribute__((weak)) sys_yield() { return -1; }
PErrorCode  __attribute__((weak)) sys_kill(pid_t pid, int sig) { return 1; }

/*
 * Process functions
 */

pid_t       __attribute__((weak)) sys_getpid(void) { return -1; }
caddr_t     __attribute__((weak)) sys_sbrk(ptrdiff_t size) { return 0; }
void        __attribute__((weak)) sys_exit(int exitCode) { for (;;) {} }

/*
 * Mutex functions
 */

PErrorCode  __attribute__((weak)) sys_create_mutex(sem_id* outHandle, const char* name, PEMutexRecursionMode recursionMode, clockid_t clockID) { return -1; }
PErrorCode  __attribute__((weak)) sys_duplicate_mutex(sem_id* outNewHandle, sem_id handle) { return -1; }
status_t __attribute__((weak)) sys_delete_mutex(sem_id handle) { return -1; }
status_t __attribute__((weak)) sys_lock_mutex(sem_id handle) { return -1; }
status_t __attribute__((weak)) sys_lock_mutex_timeout(sem_id handle, bigtime_t timeout) { return -1; }
status_t __attribute__((weak)) sys_lock_mutex_deadline(sem_id handle, bigtime_t deadline) { return -1; }
status_t __attribute__((weak)) sys_lock_mutex_clock(sem_id handle, clockid_t clockID, bigtime_t deadline) { return -1; }
status_t __attribute__((weak)) sys_try_lock_mutex(sem_id handle) { return -1; }
status_t __attribute__((weak)) sys_unlock_mutex(sem_id handle) { return -1; }

status_t __attribute__((weak)) sys_lock_mutex_shared(sem_id handle) { return -1; }
status_t __attribute__((weak)) sys_lock_mutex_shared_timeout(sem_id handle, bigtime_t timeout) { return -1; }
status_t __attribute__((weak)) sys_lock_mutex_shared_deadline(sem_id handle, bigtime_t deadline) { return -1; }
status_t __attribute__((weak)) sys_try_lock_mutex_shared(sem_id handle) { return -1; }
status_t __attribute__((weak)) sys_unlock_mutex_shared(sem_id handle) { return -1; }
status_t __attribute__((weak)) sys_islocked_mutex(sem_id handle) { return -1; }

/*
 * Condition variable functions
 */

PErrorCode __attribute__((weak)) sys_condition_var_create(handle_id* outHandle, const char* name, int clockID) { return -1; }
status_t   __attribute__((weak)) sys_condition_var_delete(handle_id handle) { return -1; }
status_t   __attribute__((weak)) sys_condition_var_wait(handle_id handle, handle_id mutexHandle) { return -1; }
status_t   __attribute__((weak)) sys_condition_var_wait_timeout(handle_id handle, handle_id mutexHandle, bigtime_t timeout) { return -1; }
status_t   __attribute__((weak)) sys_condition_var_wait_deadline(handle_id handle, handle_id mutexHandle, bigtime_t deadline) { return -1; }
status_t   __attribute__((weak)) sys_condition_var_wait_clock(handle_id handle, handle_id mutexHandle, clockid_t clockID, bigtime_t deadline) { return -1; }
status_t   __attribute__((weak)) sys_condition_var_wakeup(handle_id handle, int threadCount) { return -1; }
status_t   __attribute__((weak)) sys_condition_var_wakeup_all(handle_id handle) { return -1; }
tls_id     __attribute__((weak)) sys_thread_local_create_key(TLSDestructor_t destructor) { return -1; }
int        __attribute__((weak)) sys_thread_local_delete_key(int tls_id) { return -1; }
int        __attribute__((weak)) sys_thread_local_set(tls_id slot, const void* value) { return -1; }
void*      __attribute__((weak)) sys_thread_local_get(tls_id slot) { return NULL; }

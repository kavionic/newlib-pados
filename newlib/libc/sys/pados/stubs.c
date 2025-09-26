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

uint32_t __attribute__((weak)) _estack;


void* __attribute__((weak)) __aeabi_read_tp(void) { return NULL; }
//link_warning(__aeabi_read_tp, "__aeabi_read_tp is not implemented and will always fail");

void __attribute__((weak)) Reset_Handler(void) {}
void __attribute__((weak)) NonMaskableInt_Handler(void) {}
void __attribute__((weak)) HardFault_Handler(void) {}
void __attribute__((weak)) MemoryManagement_Handler(void) {}
void __attribute__((weak)) BusFault_Handler(void) {}
void __attribute__((weak)) UsageFault_Handler(void) {}
void __attribute__((weak)) SVCall_Handler(void) {}
void __attribute__((weak)) DebugMonitor_Handler(void) {}
void __attribute__((weak)) PendSV_Handler(void) {}
void __attribute__((weak)) SysTick_Handler(void) {}
void __attribute__((weak)) KernelHandleIRQ(void) {}

int __attribute__((weak)) pthread_setcancelstate(int state, int* oldstate) { return -1;  }

/*
 * IO functions
 */

int         __attribute__((weak)) sys_open(const char* path, int flags, mode_t mode) { return -1; }
int         __attribute__((weak)) sys_openat(int dirfd, const char* path, int flags, mode_t mode) { return -1; }
int         __attribute__((weak)) sys_close(int file) { return -1; }
PErrorCode  __attribute__((weak)) sys_fcntl(int file, int cmd, int arg, int* outResult) { return 1; }
int         __attribute__((weak)) sys_dup(int oldFile) { return -1; }
int         __attribute__((weak)) sys_dup2(int oldFile, int newFile) { return -1; }
int         __attribute__((weak)) sys_rename(const char* oldPath, const char* newPath) { return -1; }
int         __attribute__((weak)) sys_fstat(int file, struct stat* buf) { return -1; }
int         __attribute__((weak)) sys_stat(const char* path, struct stat* buf) { return -1; }
int         __attribute__((weak)) sys_write_stat(int file, const struct stat* value, uint32_t mask) { return -1; }
int         __attribute__((weak)) sys_isatty(int file) { return -1; }
off64_t     __attribute__((weak)) sys_lseek(int file, off64_t offset, int whence) { return -1; }
ssize_t     __attribute__((weak)) sys_read(int file, void* buffer, size_t length) { return -1; }
ssize_t     __attribute__((weak)) sys_write(int file, const void* buffer, size_t length) { return -1; }
int         __attribute__((weak)) sys_create_directory(const char* name, mode_t permission) { return -1; }
int         __attribute__((weak)) sys_create_directory_base(int baseFolderFD, const char* name, int permission) { return -1; }
int         __attribute__((weak)) sys_unlink_file(int dirfd, const char* path) { return -1; }
int         __attribute__((weak)) sys_remove_directory(int dirfd, const char* path) { return -1; }
PErrorCode  __attribute__((weak)) sys_readlink(int dirfd, const char* path, char* buffer, size_t bufferSize, size_t* outResultLength) { return 1; }
PErrorCode  __attribute__((weak)) sys_symlink(const char* targetPath, int dirfd, const char* symlinkPath) { return 1; }
int         __attribute__((weak)) sys_chdir(const char* path) { return -1; }
char*       __attribute__((weak)) sys_getcwd(char* pathBuffer, size_t bufferSize) { return NULL; }

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
PErrorCode  __attribute__((weak)) sys_thread_kill(pid_t pid, int sig) { return -1; }

/*
 * Process functions
 */

pid_t       __attribute__((weak)) sys_getpid(void) { return -1; }
PErrorCode  __attribute__((weak)) sys_kill(pid_t pid, int sig) { return -1; }
caddr_t     __attribute__((weak)) sys_sbrk(ptrdiff_t size) { return 0; }
void        __attribute__((weak)) sys_exit(int exitCode) { for (;;) {} }
PErrorCode  __attribute__((weak)) sys_sysconf(int name, long* outValue) { return -1; }

/*
 * Semaphore functions
 */

PErrorCode __attribute__((weak)) sys_semaphore_create(sem_id* outHandle, const char* name, clockid_t clockID, int count) { return 1; }
PErrorCode __attribute__((weak)) sys_semaphore_duplicate(sem_id* outNewHandle, sem_id handle) { return 1; }
PErrorCode __attribute__((weak)) sys_semaphore_delete(sem_id handle) { return 1; }
PErrorCode __attribute__((weak)) sys_semaphore_create_public(sem_id* outHandle, const char* name, clockid_t clockID, int flags, mode_t mode, int count) { return 1; }
PErrorCode __attribute__((weak)) sys_semaphore_unlink_public(const char* name) { return 1; }
PErrorCode __attribute__((weak)) sys_semaphore_acquire(sem_id handle) { return 1; }
PErrorCode __attribute__((weak)) sys_semaphore_acquire_timeout(sem_id handle, bigtime_t timeout) { return 1; }
PErrorCode __attribute__((weak)) sys_semaphore_acquire_deadline(sem_id handle, bigtime_t deadline) { return 1; }
PErrorCode __attribute__((weak)) sys_semaphore_acquire_clock(sem_id handle, clockid_t clockID, bigtime_t deadline) { return 1; }
PErrorCode __attribute__((weak)) sys_semaphore_try_acquire(sem_id handle) { return 1; }
PErrorCode __attribute__((weak)) sys_semaphore_release(sem_id handle) { return 1; }
PErrorCode __attribute__((weak)) sys_semaphore_get_count(sem_id handle, int* outCount) { return 1; }

/*
 * Mutex functions
 */

PErrorCode __attribute__((weak)) sys_mutex_create(sem_id* outHandle, const char* name, PEMutexRecursionMode recursionMode, clockid_t clockID) { return 1; }
PErrorCode __attribute__((weak)) sys_mutex_duplicate(sem_id* outNewHandle, sem_id handle) { return 1; }
PErrorCode __attribute__((weak)) sys_mutex_delete(sem_id handle) { return 1; }
PErrorCode __attribute__((weak)) sys_mutex_lock(sem_id handle) { return 1; }
PErrorCode __attribute__((weak)) sys_mutex_lock_timeout(sem_id handle, bigtime_t timeout) { return 1; }
PErrorCode __attribute__((weak)) sys_mutex_lock_deadline(sem_id handle, bigtime_t deadline) { return 1; }
PErrorCode __attribute__((weak)) sys_mutex_lock_clock(sem_id handle, clockid_t clockID, bigtime_t deadline) { return 1; }
PErrorCode __attribute__((weak)) sys_mutex_try_lock(sem_id handle) { return 1; }
PErrorCode __attribute__((weak)) sys_mutex_unlock(sem_id handle) { return 1; }

PErrorCode __attribute__((weak)) sys_mutex_lock_shared(sem_id handle) { return 1; }
PErrorCode __attribute__((weak)) sys_mutex_lock_shared_timeout(sem_id handle, bigtime_t timeout) { return 1; }
PErrorCode __attribute__((weak)) sys_mutex_lock_shared_deadline(sem_id handle, bigtime_t deadline) { return 1; }
PErrorCode __attribute__((weak)) sys_mutex_lock_shared_clock(sem_id handle, clockid_t clockID, bigtime_t deadline) { return 1; }
PErrorCode __attribute__((weak)) sys_mutex_try_lock_shared(sem_id handle) { return 1; }
PErrorCode __attribute__((weak)) sys_mutex_islocked(sem_id handle) { return 1; }

/*
 * Condition variable functions
 */

PErrorCode __attribute__((weak)) sys_condition_var_create(handle_id* outHandle, const char* name, int clockID) { return -1; }
PErrorCode __attribute__((weak)) sys_condition_var_delete(handle_id handle) { return -1; }
PErrorCode __attribute__((weak)) sys_condition_var_wait(handle_id handle, handle_id mutexHandle) { return -1; }
PErrorCode __attribute__((weak)) sys_condition_var_wait_timeout(handle_id handle, handle_id mutexHandle, bigtime_t timeout) { return -1; }
PErrorCode __attribute__((weak)) sys_condition_var_wait_deadline(handle_id handle, handle_id mutexHandle, bigtime_t deadline) { return -1; }
PErrorCode __attribute__((weak)) sys_condition_var_wait_clock(handle_id handle, handle_id mutexHandle, clockid_t clockID, bigtime_t deadline) { return -1; }
PErrorCode __attribute__((weak)) sys_condition_var_wakeup(handle_id handle, int threadCount) { return -1; }
PErrorCode __attribute__((weak)) sys_condition_var_wakeup_all(handle_id handle) { return -1; }

/*
 * Thread local functions
 */

tls_id     __attribute__((weak)) sys_thread_local_create_key(TLSDestructor_t destructor) { return -1; }
int        __attribute__((weak)) sys_thread_local_delete_key(int tls_id) { return -1; }
int        __attribute__((weak)) sys_thread_local_set(tls_id slot, const void* value) { return -1; }
void*      __attribute__((weak)) sys_thread_local_get(tls_id slot) { return NULL; }

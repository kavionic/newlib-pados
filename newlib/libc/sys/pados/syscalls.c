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




PADOS_SYSCALL(int       , open, (const char* path, int flags, mode_t mode));
PADOS_SYSCALL(int       , openat, (int dirfd, const char* path, int flags, mode_t mode));
PADOS_SYSCALL(int       , close, (int file));
PADOS_SYSCALL(PErrorCode, fcntl, (int file, int cmd, int arg, int* outResult));
PADOS_SYSCALL(int       , dup, (int oldFile));
PADOS_SYSCALL(int       , dup2, (int oldFile, int newFile));
PADOS_SYSCALL(int       , rename, (const char* oldPath, const char* newPath));
PADOS_SYSCALL(int       , fstat, (int file, struct stat* buf));
PADOS_SYSCALL(int       , stat, (const char* path, struct stat* buf));
PADOS_SYSCALL(int       , write_stat, (int file, const struct stat* value, uint32_t mask));
PADOS_SYSCALL(int       , isatty, (int file));
PADOS_SYSCALL(off64_t   , lseek, (int file, off64_t offset, int whence));
PADOS_SYSCALL(PErrorCode, read, (int file, void* buffer, size_t length, ssize_t* outLength));
PADOS_SYSCALL(PErrorCode, read_pos, (int file, void* buffer, size_t length, off_t position, ssize_t* outLength));
PADOS_SYSCALL(PErrorCode, readv, (int file, const struct iovec* segments, size_t segmentCount, ssize_t* outLength));
PADOS_SYSCALL(PErrorCode, readv_pos, (int file, const struct iovec* segments, size_t segmentCount, off_t position, ssize_t* outLength));
PADOS_SYSCALL(PErrorCode, write, (int file, const void* buffer, size_t length, ssize_t* outLength));
PADOS_SYSCALL(PErrorCode, write_pos, (int file, const void* buffer, size_t length, off_t position, ssize_t* outLength));
PADOS_SYSCALL(PErrorCode, writev, (int file, const struct iovec* segments, size_t segmentCount, ssize_t* outLength));
PADOS_SYSCALL(PErrorCode, writev_pos, (int file, const struct iovec* segments, size_t segmentCount, off_t position, ssize_t* outLength));
PADOS_SYSCALL(int       , create_directory, (const char* name, mode_t permission));
PADOS_SYSCALL(int       , create_directory_base, (int baseFolderFD, const char* name, int permission));
PADOS_SYSCALL(int       , read_directory, (int handle, dirent_t* entry, size_t bufSize));
PADOS_SYSCALL(int       , unlink_file, (int dirfd, const char* path));
PADOS_SYSCALL(int       , remove_directory, (int dirfd, const char* path));
PADOS_SYSCALL(PErrorCode, readlink, (int dirfd, const char* path, char* buffer, size_t bufferSize, size_t* outResultLength));
PADOS_SYSCALL(PErrorCode, symlink, (const char* targetPath, int dirfd, const char* symlinkPath));
PADOS_SYSCALL(int       , chdir, (const char* path));
PADOS_SYSCALL(char*     , getcwd, (char* pathBuffer, size_t bufferSize));
PADOS_SYSCALL(bigtime_t , get_system_time, ());
PADOS_SYSCALL(bigtime_t , get_system_time_hires, ());
PADOS_SYSCALL(bigtime_t , get_real_time, ());
PADOS_SYSCALL(PErrorCode, set_real_time, (bigtime_t time, bool updateRTC));
PADOS_SYSCALL(bigtime_t , get_clock_time_offset, (clockid_t clockID));
PADOS_SYSCALL(bigtime_t , get_clock_time, (clockid_t clockID));
PADOS_SYSCALL(bigtime_t , get_idle_time, ());

PADOS_SYSCALL(bigtime_t , get_clock_time_hires, (clockid_t clockID));
PADOS_SYSCALL(status_t  , get_clock_resolution, (clockid_t clockID, bigtime_t* outResolutionNanos));
PADOS_SYSCALL(status_t  , set_clock_resolution, (clockid_t clockID, bigtime_t resolutionNanos));
PADOS_SYSCALL(int       , thread_attribs_init, (PThreadAttribs* attribs));
PADOS_SYSCALL(PErrorCode, thread_spawn, (thread_id* outHandle, const PThreadAttribs* attribs, ThreadEntryPoint_t entryPoint, void* arguments));
PADOS_SYSCALL(void      , thread_exit, (void* returnValue));
PADOS_SYSCALL(int       , thread_detach, (thread_id handle));
PADOS_SYSCALL(int       , thread_join, (thread_id handle, void** outReturnValue));
PADOS_SYSCALL(thread_id , get_thread_id, ());
PADOS_SYSCALL(int       , thread_set_priority, (thread_id handle, int priority));
PADOS_SYSCALL(int       , thread_get_priority, (thread_id handle, int* outPriority));
PADOS_SYSCALL(int       , get_thread_info, (handle_id handle, ThreadInfo* info));
PADOS_SYSCALL(int       , get_next_thread_info, (ThreadInfo* info));
PADOS_SYSCALL(PErrorCode, snooze_ns, (bigtime_t delayNanos));
PADOS_SYSCALL(PErrorCode, snooze_until, (bigtime_t resumeTimeNanos));
PADOS_SYSCALL(int       , yield, ());
PADOS_SYSCALL(PErrorCode, thread_kill, (pid_t pid, int sig));
PADOS_SYSCALL(pid_t     , getpid, (void));
PADOS_SYSCALL(PErrorCode, kill, (pid_t pid, int sig));
PADOS_SYSCALL(caddr_t   , sbrk, (ptrdiff_t size));
PADOS_SYSCALL(void      , exit, (int exitCode));
PADOS_SYSCALL(PErrorCode, sysconf, (int name, long* outValue));
PADOS_SYSCALL(PErrorCode, semaphore_create, (sem_id* outHandle, const char* name, clockid_t clockID, int count));
PADOS_SYSCALL(PErrorCode, semaphore_duplicate, (sem_id* outNewHandle, sem_id handle));
PADOS_SYSCALL(PErrorCode, semaphore_delete, (sem_id handle));
PADOS_SYSCALL(PErrorCode, semaphore_create_public, (sem_id* outHandle, const char* name, clockid_t clockID, int flags, mode_t mode, int count));
PADOS_SYSCALL(PErrorCode, semaphore_unlink_public, (const char* name));
PADOS_SYSCALL(PErrorCode, semaphore_acquire, (sem_id handle));
PADOS_SYSCALL(PErrorCode, semaphore_acquire_timeout_ns, (sem_id handle, bigtime_t timeout));
PADOS_SYSCALL(PErrorCode, semaphore_acquire_deadline_ns, (sem_id handle, bigtime_t deadline));
PADOS_SYSCALL(PErrorCode, semaphore_acquire_clock_ns, (sem_id handle, clockid_t clockID, bigtime_t deadline));
PADOS_SYSCALL(PErrorCode, semaphore_try_acquire, (sem_id handle));
PADOS_SYSCALL(PErrorCode, semaphore_release, (sem_id handle));
PADOS_SYSCALL(PErrorCode, semaphore_get_count, (sem_id handle, int* outCount));
PADOS_SYSCALL(PErrorCode, mutex_create, (sem_id* outHandle, const char* name, PEMutexRecursionMode recursionMode, clockid_t clockID));
PADOS_SYSCALL(PErrorCode, mutex_duplicate, (sem_id* outNewHandle, sem_id handle));
PADOS_SYSCALL(PErrorCode, mutex_delete, (sem_id handle));
PADOS_SYSCALL(PErrorCode, mutex_lock, (sem_id handle));
PADOS_SYSCALL(PErrorCode, mutex_lock_timeout_ns, (sem_id handle, bigtime_t timeout));
PADOS_SYSCALL(PErrorCode, mutex_lock_deadline_ns, (sem_id handle, bigtime_t deadline));
PADOS_SYSCALL(PErrorCode, mutex_lock_clock_ns, (sem_id handle, clockid_t clockID, bigtime_t deadline));
PADOS_SYSCALL(PErrorCode, mutex_try_lock, (sem_id handle));
PADOS_SYSCALL(PErrorCode, mutex_unlock, (sem_id handle));
PADOS_SYSCALL(PErrorCode, mutex_lock_shared, (sem_id handle));
PADOS_SYSCALL(PErrorCode, mutex_lock_shared_timeout_ns, (sem_id handle, bigtime_t timeout));
PADOS_SYSCALL(PErrorCode, mutex_lock_shared_deadline_ns, (sem_id handle, bigtime_t deadline));
PADOS_SYSCALL(PErrorCode, mutex_lock_shared_clock_ns, (sem_id handle, clockid_t clockID, bigtime_t deadline));
PADOS_SYSCALL(PErrorCode, mutex_try_lock_shared, (sem_id handle));
PADOS_SYSCALL(PErrorCode, mutex_islocked, (sem_id handle));
PADOS_SYSCALL(PErrorCode, condition_var_create, (handle_id* outHandle, const char* name, clockid_t clockID));
PADOS_SYSCALL(PErrorCode, condition_var_delete, (handle_id handle));
PADOS_SYSCALL(PErrorCode, condition_var_wait, (handle_id handle, handle_id mutexHandle));
PADOS_SYSCALL(PErrorCode, condition_var_wait_timeout_ns, (handle_id handle, handle_id mutexHandle, bigtime_t timeout));
PADOS_SYSCALL(PErrorCode, condition_var_wait_deadline_ns, (handle_id handle, handle_id mutexHandle, bigtime_t deadline));
PADOS_SYSCALL(PErrorCode, condition_var_wait_clock_ns, (handle_id handle, handle_id mutexHandle, clockid_t clockID, bigtime_t deadline));
PADOS_SYSCALL(PErrorCode, condition_var_wakeup, (handle_id handle, int threadCount));
PADOS_SYSCALL(PErrorCode, condition_var_wakeup_all, (handle_id handle));
PADOS_SYSCALL(tls_id    , thread_local_create_key, (TLSDestructor_t destructor));
PADOS_SYSCALL(int       , thread_local_delete_key, (int tls_id));
PADOS_SYSCALL(int       , thread_local_set, (tls_id slot, const void* value));
PADOS_SYSCALL(void*     , thread_local_get, (tls_id slot));
PADOS_SYSCALL(PErrorCode, reboot, (BootMode bootMode));

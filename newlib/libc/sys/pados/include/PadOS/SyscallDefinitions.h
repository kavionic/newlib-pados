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

#ifndef PEXPAND_SYSCALL
#error PEXPAND_SYSCALL must be defined before including this file.
#endif

 /*
  * IO functions
  */

PEXPAND_SYSCALL(PSysRetPair,    open,               (const char* path, int flags, mode_t mode))
PEXPAND_SYSCALL(PSysRetPair,    openat,             (int dirfd, const char* path, int flags, mode_t mode))
PEXPAND_SYSCALL(PSysRetPair,    reopen_file,        (int oldHandle, int openFlags))
PEXPAND_SYSCALL(PErrorCode,     close,              (int file))
PEXPAND_SYSCALL(PErrorCode,     fcntl,              (int file, int cmd, int arg, int* outResult))
PEXPAND_SYSCALL(PSysRetPair,    dup,                (int oldFile))
PEXPAND_SYSCALL(PSysRetPair,    dup2,               (int oldFile, int newFile))
PEXPAND_SYSCALL(PErrorCode,     rename,             (const char* oldPath, const char* newPath))
PEXPAND_SYSCALL(PErrorCode,     fstat,              (int file, struct stat* buf))
PEXPAND_SYSCALL(PErrorCode,     stat,               (const char* path, struct stat* buf))
PEXPAND_SYSCALL(PErrorCode,     write_stat,         (int file, const struct stat* value, uint32_t mask))
PEXPAND_SYSCALL(PErrorCode,     isatty,             (int file))
PEXPAND_SYSCALL(PErrorCode,     seek,               (int file, off_t* ioOffset, int whence))
PEXPAND_SYSCALL(PSysRetPair,    read,               (int file, void* buffer, size_t length))
PEXPAND_SYSCALL(PSysRetPair,    read_pos,           (int file, void* buffer, size_t length, off_t position))
PEXPAND_SYSCALL(PSysRetPair,    readv,              (int file, const struct iovec* segments, size_t segmentCount))
PEXPAND_SYSCALL(PSysRetPair,    readv_pos,          (int file, const struct iovec* segments, size_t segmentCount, off_t position))
PEXPAND_SYSCALL(PSysRetPair,    write,              (int file, const void* buffer, size_t length))
PEXPAND_SYSCALL(PSysRetPair,    write_pos,          (int file, const void* buffer, size_t length, off_t position))
PEXPAND_SYSCALL(PSysRetPair,    writev,             (int file, const struct iovec* segments, size_t segmentCount))
PEXPAND_SYSCALL(PSysRetPair,    writev_pos,         (int file, const struct iovec* segments, size_t segmentCount, off_t position))
PEXPAND_SYSCALL(PErrorCode,     device_control,     (int handle, int request, const void* inData, size_t inDataLength, void* outData, size_t outDataLength))

PEXPAND_SYSCALL(PErrorCode,     fsync,              (int file))
PEXPAND_SYSCALL(PErrorCode,     create_directory,   (int dirfd, const char* name, mode_t permission))
PEXPAND_SYSCALL(PSysRetPair,    read_directory,     (int handle, dirent_t* entry, size_t bufSize))
PEXPAND_SYSCALL(PErrorCode,     rewind_directory,   (int handle))

PEXPAND_SYSCALL(PErrorCode,     unlink_file,        (int dirfd, const char* path))
PEXPAND_SYSCALL(PErrorCode,     remove_directory,   (int dirfd, const char* path))
PEXPAND_SYSCALL(PSysRetPair,    readlink,           (int dirfd, const char* path, char* buffer, size_t bufferSize))
PEXPAND_SYSCALL(PErrorCode,     symlink,            (const char* targetPath, int dirfd, const char* symlinkPath))
PEXPAND_SYSCALL(PErrorCode,     chdir,              (const char* path))
PEXPAND_SYSCALL(PErrorCode,     getcwd,             (char* pathBuffer, size_t bufferSize))

PEXPAND_SYSCALL(PErrorCode,     mount,              (const char* devicePath, const char* directoryPath, const char* filesystemName, uint32_t flags, const char* args, size_t argLength))

PEXPAND_SYSCALL(PErrorCode,     get_directory_path, (int handle, char* buffer, size_t bufferSize))

/*
 * Time functions
 */

PEXPAND_SYSCALL(PErrorCode,     get_monotonic_time_ns,      (time_t* outTime))
PEXPAND_SYSCALL(PErrorCode,     get_monotonic_time_hires_ns,(time_t* outTime))
PEXPAND_SYSCALL(PErrorCode,     get_real_time_ns,           (time_t* outTime))
PEXPAND_SYSCALL(PErrorCode,     get_real_time_hires_ns,     (time_t* outTime))
PEXPAND_SYSCALL(PErrorCode,     set_real_time_ns,           (time_t time, bool updateRTC))
PEXPAND_SYSCALL(PErrorCode,     get_clock_time_offset_ns,   (clockid_t clockID, time_t* outOffset))
PEXPAND_SYSCALL(PErrorCode,     get_clock_time_ns,          (clockid_t clockID, time_t* outTime))
PEXPAND_SYSCALL(PErrorCode,     get_idle_time_ns,           (time_t* outTime))

PEXPAND_SYSCALL(PErrorCode,     get_clock_time_hires_ns,    (clockid_t clockID, time_t* outTime))
PEXPAND_SYSCALL(PErrorCode,     get_clock_resolution_ns,    (clockid_t clockID, time_t* outResolutionNanos))
PEXPAND_SYSCALL(PErrorCode,     set_clock_resolution_ns,    (clockid_t clockID, time_t resolutionNanos))

/*
 * Thread functions
 */

PEXPAND_SYSCALL(PErrorCode,     thread_attribs_init,    (PThreadAttribs* attribs))
PEXPAND_SYSCALL(PErrorCode,     thread_spawn,           (thread_id* outHandle, const PThreadAttribs* attribs, ThreadEntryPoint_t entryPoint, void* arguments))
PEXPAND_SYSCALL(__attribute__((noreturn)) void, thread_exit, (void* returnValue))
PEXPAND_SYSCALL(PErrorCode,     thread_detach,          (thread_id handle))
PEXPAND_SYSCALL(PErrorCode,     thread_join,            (thread_id handle, void** outReturnValue))
PEXPAND_SYSCALL(thread_id,      get_thread_id,          ())
PEXPAND_SYSCALL(PErrorCode,     thread_set_priority,    (thread_id handle, int priority))
PEXPAND_SYSCALL(PErrorCode,     thread_get_priority,    (thread_id handle, int* outPriority))
PEXPAND_SYSCALL(PErrorCode,     get_thread_info,        (handle_id handle, ThreadInfo* info))
PEXPAND_SYSCALL(PErrorCode,     get_next_thread_info,   (ThreadInfo* info))
PEXPAND_SYSCALL(PErrorCode,     snooze_ns,              (bigtime_t delayNanos))
PEXPAND_SYSCALL(PErrorCode,     snooze_until,           (bigtime_t resumeTimeNanos))
PEXPAND_SYSCALL(PErrorCode,     yield,                  ())
PEXPAND_SYSCALL(PErrorCode,     thread_kill,            (pid_t pid, int sig))

/*
 * Process functions
 */

PEXPAND_SYSCALL(PSysRetPair,    getpid,     (void))
PEXPAND_SYSCALL(PErrorCode,     kill,       (pid_t pid, int sig))
PEXPAND_SYSCALL(PSysRetPair,    sbrk,       (ptrdiff_t size))
PEXPAND_SYSCALL(__attribute__((noreturn)) void, exit, (int exitCode))
PEXPAND_SYSCALL(PErrorCode,     sysconf,    (int name, long* outValue))
PEXPAND_SYSCALL(PErrorCode,     reboot,     (BootMode bootMode))

/*
 * Semaphore functions
 */

PEXPAND_SYSCALL(PErrorCode,     semaphore_create,               (sem_id* outHandle, const char* name, clockid_t clockID, int count))
PEXPAND_SYSCALL(PErrorCode,     semaphore_duplicate,            (sem_id* outNewHandle, sem_id handle))
PEXPAND_SYSCALL(PErrorCode,     semaphore_delete,               (sem_id handle))
PEXPAND_SYSCALL(PErrorCode,     semaphore_create_public,        (sem_id* outHandle, const char* name, clockid_t clockID, int flags, mode_t mode, int count))
PEXPAND_SYSCALL(PErrorCode,     semaphore_unlink_public,        (const char* name))
PEXPAND_SYSCALL(PErrorCode,     semaphore_acquire,              (sem_id handle))
PEXPAND_SYSCALL(PErrorCode,     semaphore_acquire_timeout_ns,   (sem_id handle, bigtime_t timeout))
PEXPAND_SYSCALL(PErrorCode,     semaphore_acquire_deadline_ns,  (sem_id handle, bigtime_t deadline))
PEXPAND_SYSCALL(PErrorCode,     semaphore_acquire_clock_ns,     (sem_id handle, clockid_t clockID, bigtime_t deadline))
PEXPAND_SYSCALL(PErrorCode,     semaphore_try_acquire,          (sem_id handle))
PEXPAND_SYSCALL(PErrorCode,     semaphore_release,              (sem_id handle))
PEXPAND_SYSCALL(PErrorCode,     semaphore_get_count,            (sem_id handle, int* outCount))

/*
 * Mutex functions
 */

PEXPAND_SYSCALL(PErrorCode,   mutex_create,                     (sem_id* outHandle, const char* name, PEMutexRecursionMode recursionMode, clockid_t clockID))
PEXPAND_SYSCALL(PErrorCode,   mutex_duplicate,                  (sem_id* outNewHandle, sem_id handle))
PEXPAND_SYSCALL(PErrorCode,   mutex_delete,                     (sem_id handle))
PEXPAND_SYSCALL(PErrorCode,   mutex_lock,                       (sem_id handle))
PEXPAND_SYSCALL(PErrorCode,   mutex_lock_timeout_ns,            (sem_id handle, bigtime_t timeout))
PEXPAND_SYSCALL(PErrorCode,   mutex_lock_deadline_ns,           (sem_id handle, bigtime_t deadline))
PEXPAND_SYSCALL(PErrorCode,   mutex_lock_clock_ns,              (sem_id handle, clockid_t clockID, bigtime_t deadline))
PEXPAND_SYSCALL(PErrorCode,   mutex_try_lock,                   (sem_id handle))
PEXPAND_SYSCALL(PErrorCode,   mutex_unlock,                     (sem_id handle))
PEXPAND_SYSCALL(PErrorCode,   mutex_lock_shared,                (sem_id handle))
PEXPAND_SYSCALL(PErrorCode,   mutex_lock_shared_timeout_ns,     (sem_id handle, bigtime_t timeout))
PEXPAND_SYSCALL(PErrorCode,   mutex_lock_shared_deadline_ns,    (sem_id handle, bigtime_t deadline))
PEXPAND_SYSCALL(PErrorCode,   mutex_lock_shared_clock_ns,       (sem_id handle, clockid_t clockID, bigtime_t deadline))
PEXPAND_SYSCALL(PErrorCode,   mutex_try_lock_shared,            (sem_id handle))
PEXPAND_SYSCALL(PErrorCode,   mutex_islocked,                   (sem_id handle))

/*
 * Condition variable functions
 */

PEXPAND_SYSCALL(PErrorCode,   condition_var_create,             (handle_id* outHandle, const char* name, clockid_t clockID))
PEXPAND_SYSCALL(PErrorCode,   condition_var_delete,             (handle_id handle))
PEXPAND_SYSCALL(PErrorCode,   condition_var_wait,               (handle_id handle, handle_id mutexHandle))
PEXPAND_SYSCALL(PErrorCode,   condition_var_wait_timeout_ns,    (handle_id handle, handle_id mutexHandle, bigtime_t timeout))
PEXPAND_SYSCALL(PErrorCode,   condition_var_wait_deadline_ns,   (handle_id handle, handle_id mutexHandle, bigtime_t deadline))
PEXPAND_SYSCALL(PErrorCode,   condition_var_wait_clock_ns,      (handle_id handle, handle_id mutexHandle, clockid_t clockID, bigtime_t deadline))
PEXPAND_SYSCALL(PErrorCode,   condition_var_wakeup,             (handle_id handle, int threadCount))
PEXPAND_SYSCALL(PErrorCode,   condition_var_wakeup_all,         (handle_id handle))

/*
 * Thread local functions
 */

PEXPAND_SYSCALL(PErrorCode, thread_local_create_key,    (tls_id* outKey, TLSDestructor_t destructor))
PEXPAND_SYSCALL(PErrorCode, thread_local_delete_key,    (tls_id key))

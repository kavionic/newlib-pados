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
#include <sys/dirent.h>
#include <sys/cdefs.h>
#include <stdbool.h>
#include <sys/pados_types.h>
#include <sys/pados_error_codes.h>
#include <sys/pados_threads.h>
#include <sys/pados_mutex.h>
#include <PadOS/BootMode.h>

#ifdef __cplusplus
extern "C" {
#endif

struct iovec;

typedef void (*TLSDestructor_t)(void*);

/*
 * IO functions
 */

int         __open(const char* path, int flags, mode_t mode);
int         __openat(int dirfd, const char* path, int flags, mode_t mode);
int         __close(int file);
PErrorCode  __fcntl(int file, int cmd, int arg, int* outResult);
int         __dup(int oldFile);
int         __dup2(int oldFile, int newFile);
int         __rename(const char* oldPath, const char* newPath);
int         __fstat(int file, struct stat* buf);
int         __stat(const char* path, struct stat* buf);
int         __write_stat(int file, const struct stat* value, uint32_t mask);
int         __isatty(int file);
off64_t     __lseek(int file, off64_t offset, int whence);
PErrorCode  __read(int file, void* buffer, size_t length, ssize_t* outLength);
PErrorCode  __read_pos(int file, void* buffer, size_t length, off_t position, ssize_t* outLength);
PErrorCode  __readv(int file, const struct iovec* segments, size_t segmentCount, ssize_t* outLength);
PErrorCode  __readv_pos(int file, const struct iovec* segments, size_t segmentCount, off_t position, ssize_t* outLength);
PErrorCode  __write(int file, const void* buffer, size_t length, ssize_t* outLength);
PErrorCode  __write_pos(int file, const void* buffer, size_t length, off_t position, ssize_t* outLength);
PErrorCode  __writev(int file, const struct iovec* segments, size_t segmentCount, ssize_t* outLength);
PErrorCode  __writev_pos(int file, const struct iovec* segments, size_t segmentCount, off_t position, ssize_t* outLength);
int         __create_directory(const char* name, mode_t permission);
int         __create_directory_base(int baseFolderFD, const char* name, int permission);
int         __read_directory(int handle, dirent_t* entry, size_t bufSize);
int         __unlink_file(int dirfd, const char* path);
int         __remove_directory(int dirfd, const char* path);
PErrorCode  __readlink(int dirfd, const char* path, char* buffer, size_t bufferSize, size_t* outResultLength);
PErrorCode  __symlink(const char* targetPath, int dirfd, const char* symlinkPath);
int         __chdir(const char* path);
char*       __getcwd(char* pathBuffer, size_t bufferSize);

/*
 * Time functions
 */

bigtime_t __get_system_time();
bigtime_t __get_system_time_hires();
bigtime_t __get_real_time();
PErrorCode  __set_real_time(bigtime_t time, bool updateRTC);
bigtime_t __get_clock_time_offset(clockid_t clockID);
bigtime_t __get_clock_time(clockid_t clockID);
bigtime_t __get_idle_time();
bigtime_t __get_clock_time_hires(clockid_t clockID);
status_t  __get_clock_resolution(clockid_t clockID, bigtime_t* outResolutionNanos);
status_t  __set_clock_resolution(clockid_t clockID, bigtime_t resolutionNanos);

/*
 * Thread functions
 */

int         __thread_attribs_init(PThreadAttribs* attribs);
PErrorCode  __thread_spawn(thread_id* outHandle, const PThreadAttribs* attribs, ThreadEntryPoint_t entryPoint, void* arguments);
void        __thread_exit(void* returnValue);
int         __thread_detach(thread_id handle);
int         __thread_join(thread_id handle, void** outReturnValue);
thread_id   __get_thread_id();
int         __thread_set_priority(thread_id handle, int priority);
int         __thread_get_priority(thread_id handle, int* outPriority);
int         __get_thread_info(handle_id handle, ThreadInfo* info);
int         __get_next_thread_info(ThreadInfo* info);
PErrorCode  __snooze_ns(bigtime_t delayNanos);
PErrorCode  __snooze_until(bigtime_t resumeTimeNanos);
int         __yield();
PErrorCode  __thread_kill(pid_t pid, int sig);

/*
 * Process functions
 */

pid_t       __getpid(void);
PErrorCode  __kill(pid_t pid, int sig);
caddr_t     __sbrk(ptrdiff_t size);
void        __exit(int exitCode) _ATTRIBUTE((__noreturn__));
PErrorCode  __sysconf(int name, long* outValue);
PErrorCode  __reboot(BootMode bootMode);

/*
 * Semaphore functions
 */

PErrorCode __semaphore_create(sem_id* outHandle, const char* name, clockid_t clockID, int count);
PErrorCode __semaphore_duplicate(sem_id* outNewHandle, sem_id handle);
PErrorCode __semaphore_delete(sem_id handle);
PErrorCode __semaphore_create_public(sem_id* outHandle, const char* name, clockid_t clockID, int flags, mode_t mode, int count);
PErrorCode __semaphore_unlink_public(const char* name);
PErrorCode __semaphore_acquire(sem_id handle);
PErrorCode __semaphore_acquire_timeout_ns(sem_id handle, bigtime_t timeout);
PErrorCode __semaphore_acquire_deadline_ns(sem_id handle, bigtime_t deadline);
PErrorCode __semaphore_acquire_clock_ns(sem_id handle, clockid_t clockID, bigtime_t deadline);
PErrorCode __semaphore_try_acquire(sem_id handle);
PErrorCode __semaphore_release(sem_id handle);
PErrorCode __semaphore_get_count(sem_id handle, int* outCount);

/*
 * Mutex functions
 */

PErrorCode __mutex_create(sem_id* outHandle, const char* name, PEMutexRecursionMode recursionMode, clockid_t clockID);
PErrorCode __mutex_duplicate(sem_id* outNewHandle, sem_id handle);
PErrorCode __mutex_delete(sem_id handle);
PErrorCode __mutex_lock(sem_id handle);
PErrorCode __mutex_lock_timeout_ns(sem_id handle, bigtime_t timeout);
PErrorCode __mutex_lock_deadline_ns(sem_id handle, bigtime_t deadline);
PErrorCode __mutex_lock_clock_ns(sem_id handle, clockid_t clockID, bigtime_t deadline);
PErrorCode __mutex_try_lock(sem_id handle);
PErrorCode __mutex_unlock(sem_id handle);

PErrorCode __mutex_lock_shared(sem_id handle);
PErrorCode __mutex_lock_shared_timeout_ns(sem_id handle, bigtime_t timeout);
PErrorCode __mutex_lock_shared_deadline_ns(sem_id handle, bigtime_t deadline);
PErrorCode __mutex_lock_shared_clock_ns(sem_id handle, clockid_t clockID, bigtime_t deadline);
PErrorCode __mutex_try_lock_shared(sem_id handle);
PErrorCode __mutex_islocked(sem_id handle);

/*
 * Condition variable functions
 */

PErrorCode  __condition_var_create(handle_id* outHandle, const char* name, clockid_t clockID);
PErrorCode  __condition_var_delete(handle_id handle);
PErrorCode  __condition_var_wait(handle_id handle, handle_id mutexHandle);
PErrorCode  __condition_var_wait_timeout_ns(handle_id handle, handle_id mutexHandle, bigtime_t timeout);
PErrorCode  __condition_var_wait_deadline_ns(handle_id handle, handle_id mutexHandle, bigtime_t deadline);
PErrorCode  __condition_var_wait_clock_ns(handle_id handle, handle_id mutexHandle, clockid_t clockID, bigtime_t deadline);
PErrorCode  __condition_var_wakeup(handle_id handle, int threadCount);
PErrorCode  __condition_var_wakeup_all(handle_id handle);

/*
 * Thread local functions
 */

tls_id  __thread_local_create_key(TLSDestructor_t destructor);
int     __thread_local_delete_key(int tls_id);
int     __thread_local_set(tls_id slot, const void* value);
void*   __thread_local_get(tls_id slot);


#define SYS_open                            0 
#define SYS_openat                          1 
#define SYS_close                           2 
#define SYS_fcntl                           3 
#define SYS_dup                             4 
#define SYS_dup2                            5 
#define SYS_rename                          6 
#define SYS_fstat                           7 
#define SYS_stat                            8 
#define SYS_write_stat                      9 
#define SYS_isatty                          10
#define SYS_lseek                           11
#define SYS_read                            12
#define SYS_read_pos                        13
#define SYS_readv                           14
#define SYS_readv_pos                       15
#define SYS_write                           16
#define SYS_write_pos                       17
#define SYS_writev                          18
#define SYS_writev_pos                      19
#define SYS_create_directory                20
#define SYS_create_directory_base           21
#define SYS_read_directory                  22
#define SYS_unlink_file                     23
#define SYS_remove_directory                24
#define SYS_readlink                        25
#define SYS_symlink                         26
#define SYS_chdir                           27
#define SYS_getcwd                          28
#define SYS_get_system_time                 29
#define SYS_get_system_time_hires           30
#define SYS_get_real_time                   31
#define SYS_set_real_time                   32
#define SYS_get_clock_time_offset           33
#define SYS_get_clock_time                  34
#define SYS_get_clock_time_hires            35
#define SYS_get_clock_resolution            36
#define SYS_set_clock_resolution            37
#define SYS_thread_attribs_init             38
#define SYS_thread_spawn                    39
#define SYS_thread_exit                     40
#define SYS_thread_detach                   41
#define SYS_thread_join                     42
#define SYS_get_thread_id                   43
#define SYS_thread_set_priority             44
#define SYS_thread_get_priority             45
#define SYS_get_thread_info                 46
#define SYS_get_next_thread_info            47
#define SYS_snooze_ns                       48
#define SYS_yield                           49
#define SYS_thread_kill                     50
#define SYS_getpid                          51
#define SYS_kill                            52
#define SYS_sbrk                            53
#define SYS_exit                            54
#define SYS_sysconf                         55
#define SYS_semaphore_create                56
#define SYS_semaphore_duplicate             57
#define SYS_semaphore_delete                58
#define SYS_semaphore_create_public         59
#define SYS_semaphore_unlink_public         60
#define SYS_semaphore_acquire               61
#define SYS_semaphore_acquire_timeout_ns    62
#define SYS_semaphore_acquire_deadline_ns   63
#define SYS_semaphore_acquire_clock_ns      64
#define SYS_semaphore_try_acquire           65
#define SYS_semaphore_release               66
#define SYS_semaphore_get_count             67
#define SYS_mutex_create                    68
#define SYS_mutex_duplicate                 69
#define SYS_mutex_delete                    70
#define SYS_mutex_lock                      71
#define SYS_mutex_lock_timeout_ns           72
#define SYS_mutex_lock_deadline_ns          73
#define SYS_mutex_lock_clock_ns             74
#define SYS_mutex_try_lock                  75
#define SYS_mutex_unlock                    76
#define SYS_mutex_lock_shared               77
#define SYS_mutex_lock_shared_timeout_ns    78
#define SYS_mutex_lock_shared_deadline_ns   79
#define SYS_mutex_lock_shared_clock_ns      80
#define SYS_mutex_try_lock_shared           81
#define SYS_mutex_islocked                  82
#define SYS_condition_var_create            83
#define SYS_condition_var_delete            84
#define SYS_condition_var_wait              85
#define SYS_condition_var_wait_timeout_ns   86
#define SYS_condition_var_wait_deadline_ns  87
#define SYS_condition_var_wait_clock_ns     88
#define SYS_condition_var_wakeup            89
#define SYS_condition_var_wakeup_all        90
#define SYS_thread_local_create_key         91
#define SYS_thread_local_delete_key         92
#define SYS_thread_local_set                93
#define SYS_thread_local_get                94
#define SYS_get_idle_time                   95
#define SYS_reboot                          96
#define SYS_snooze_until                    97



#define PADOS_SYSCALL(RETTYPE, FNAME, SIGNATURE) \
  __attribute__((naked)) RETTYPE __##FNAME SIGNATURE { \
    __asm volatile ( \
        "mrs    r12, CONTROL                    \n" \
        "tst    r12, #1                         \n" \
        "beq " __XSTRING(sys_##FNAME)          "\n" \
        "ldr r12, =" __XSTRING(SYS_##FNAME)    "\n" \
        "svc 0                                  \n" \
        ::: "r12", "memory", "cc");                 \
  }


#ifdef __cplusplus
}
#endif

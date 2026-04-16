/*
 * Copyright (C) 2025-2026 Kurt Skauen. All rights reserved.
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

#include <spawn.h>
#include <sys/wait.h>

struct PThreadUserData;

#ifdef __cplusplus
enum class ObjectWaitMode : int;
enum class DigitalPinID : uint32_t;
enum class DigitalPinDirection_e : uint32_t;
enum class DigitalPinDriveStrength_e : uint32_t;
enum class PinPullMode_e : uint32_t;
enum class DigitalPinPeripheralID : int32_t;

#endif

#ifndef PEXPAND_SYSCALL
#error PEXPAND_SYSCALL must be defined before including this file.
#endif

#ifndef PEXPAND_SYSCALL_VOID
#define PEXPAND_SYSCALL_VOID PEXPAND_SYSCALL
#define PEXPAND_SYSCALL_VOID_defined
#endif

#ifndef PEXPAND_SYSCALL_NORET
#define PEXPAND_SYSCALL_NORET PEXPAND_SYSCALL
#define PEXPAND_SYSCALL_NORET_defined
#endif

 /*
  * IO functions
  */

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, int, PSysRetPair,    __, open,
    PARGS3((const char*, path), (int, flags), (mode_t, mode)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, int, PSysRetPair,    __, openat,
    PARGS4((int, dirfd), (const char*, path), (int, flags), (mode_t, mode)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, int, PSysRetPair,    , reopen_file,
    PARGS2((int, oldHandle), (int, openFlags)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode,     _, close,
    PARGS1((int, file)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,     __, fcntl,
    PARGS4((int, file), (int, cmd), (int, arg), (int*, outResult)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, int, PSysRetPair,    , dup,
    PARGS1((int, oldFile)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, int, PSysRetPair,    , dup2,
    PARGS2((int, oldFile), (int, newFile)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode,     _, rename,
    PARGS2((const char*, oldPath), (const char*, newPath)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode,     _, fstat,
    PARGS2((int, file), (struct stat*, buf)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode,     _, stat,
    PARGS2((const char*, path), (struct stat*, buf)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,     __, write_stat,
    PARGS3((int, file), (const struct stat*, value), (uint32_t, mask)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode,     _, isatty,
    PARGS1((int, file)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,     , seek,
    PARGS3((int, file), (off_t*, ioOffset), (int, whence)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, ssize_t, PSysRetPair, _, read,
    PARGS3((int, file), (void*, buffer), (size_t, length)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, ssize_t, PSysRetPair,    , pread,
    PARGS4((int, file), (void*, buffer), (size_t, length), (off_t, position)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, ssize_t, PSysRetPair, , readv,
    PARGS3((int, file), (const struct iovec*, segments), (int, segmentCount)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, ssize_t, PSysRetPair,    , preadv,
    PARGS4((int, file), (const struct iovec*, segments), (int, segmentCount), (off_t, position)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, ssize_t, PSysRetPair,    _, write,
    PARGS3((int, file), (const void*, buffer), (size_t, length)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, ssize_t, PSysRetPair,    , pwrite,
    PARGS4((int, file), (const void*, buffer), (size_t, length), (off_t, position)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, ssize_t, PSysRetPair, , writev,
    PARGS3((int, file), (const struct iovec*, segments), (int, segmentCount)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, ssize_t, PSysRetPair, , pwritev,
    PARGS4((int, file), (const struct iovec*, segments), (int, segmentCount), (off_t, position)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , device_control,
    PARGS6((int, handle), (int, request), (const void*, inData), (size_t, inDataLength), (void*, outData), (size_t, outDataLength)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, __, fsync,
    PARGS1((int, file)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode,     __, create_directory,
    PARGS3((int, dirfd), (const char*, name), (mode_t, permission)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, int, PSysRetPair, __, read_directory,
    PARGS3((int, handle), (dirent_t*, entry), (size_t, bufSize)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , rewind_directory,
    PARGS1((int, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode,     __, unlink_file,
    PARGS2((int, dirfd), (const char*, path)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode,     __, remove_directory,
    PARGS2((int, dirfd), (const char*, path)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, int, PSysRetPair, __, readlink,
    PARGS4((int, dirfd), (const char*, path), (char*, buffer), (size_t, bufferSize)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode, __, symlink,
    PARGS3((const char*, targetPath), (int, dirfd), (const char*, symlinkPath)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode, , chdir,
    PARGS1((const char*, path)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,     __, getcwd,
    PARGS2((char*, pathBuffer), (size_t, bufferSize)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , mount,
    PARGS6((const char*, devicePath), (const char*, directoryPath), (const char*, filesystemName), (uint32_t, flags), (const char*, args), (size_t, argLength)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , get_directory_path,
    PARGS3((int, handle), (char*, buffer), (size_t, bufferSize)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , get_dirty_disk_cache_blocks,
    PARGS1((size_t*, outBlocks)))


/*
 * Time functions
 */

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, time_t,     time_t, , get_monotonic_time_ns,
    PARGS0())

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, time_t,     time_t, , get_monotonic_time_hires_ns,
    PARGS0())

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, time_t,     time_t, , get_real_time_ns,
    PARGS0())

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, time_t,     time_t, , get_real_time_hires_ns,
    PARGS0())

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , set_real_time_ns,
    PARGS2((time_t, time), (bool, updateRTC)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, __, get_clock_time_offset_ns,
    PARGS2((clockid_t, clockID), (time_t*, outOffset)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, __, get_clock_time_ns,
    PARGS2((clockid_t, clockID), (time_t*, outTime)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, time_t,     time_t, , get_idle_time_ns,
    PARGS0())

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, time_t,     time_t, , get_total_irq_time_ns,
    PARGS0())

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,     __, get_clock_time_hires_ns,
    PARGS2((clockid_t, clockID), (time_t*, outTime)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,     __, get_clock_resolution_ns,
    PARGS2((clockid_t, clockID), (time_t*, outResolutionNanos)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,     __, set_clock_resolution_ns,
    PARGS2((clockid_t, clockID), (time_t, resolutionNanos)))


/*
 * Thread functions
 */

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , thread_attribs_init,
    PARGS1((PThreadAttribs*, attribs)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, __, thread_spawn,
    PARGS6((thread_id*, outHandle), (const PThreadAttribs*, attribs), (struct PThreadUserData*, threadData), (ThreadEntryTrampoline_t, entryTrampoline), (ThreadEntryPoint_t, entryPoint), (void*, arguments)))

PEXPAND_SYSCALL_NORET(_SYSEPILOGUE_passthrough, void, void, , thread_terminate,
    PARGS1((void*, returnValue)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,   , thread_cancel,
    PARGS1((pid_t, threadID)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,   , thread_setcancelstate,
    PARGS2((PThreadCancelState, state), (PThreadCancelState*, outOldState)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , thread_setcanceltype,
    PARGS2((PThreadCancelType, type), (PThreadCancelType*, outOldType)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , thread_detach,
    PARGS1((thread_id, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , thread_join,
    PARGS2((thread_id, handle), (void**, outReturnValue)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, thread_id,  thread_id, __, get_thread_id,
    PARGS0())

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , thread_set_priority,
    PARGS2((thread_id, handle), (int, priority)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,   , thread_get_priority,
    PARGS2((thread_id, handle), (int*, outPriority)))

PEXPAND_SYSCALL(_SYSEPILOGUE_cancelpnt, PErrorCode, PErrorCode,   , get_thread_info,
    PARGS2((handle_id, handle), (ThreadInfo*, info)))

PEXPAND_SYSCALL(_SYSEPILOGUE_cancelpnt, PErrorCode, PErrorCode,   , get_next_thread_info,
    PARGS1((ThreadInfo*, info)))

PEXPAND_SYSCALL(_SYSEPILOGUE_cancelpnt, PErrorCode, PErrorCode,   , snooze_ns,
    PARGS1((bigtime_t, delayNanos)))

PEXPAND_SYSCALL(_SYSEPILOGUE_cancelpnt, PErrorCode, PErrorCode,   , snooze_until_ns,
    PARGS1((bigtime_t, resumeTimeNanos)))

PEXPAND_SYSCALL(_SYSEPILOGUE_cancelpnt, PErrorCode, PErrorCode,   , yield,
    PARGS0())

/*
 * Process functions
 */


PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, int, PErrorCode, __, posix_spawn,
    PARGS7(
        (pid_t*, outPID),
        (ThreadEntryTrampoline_t, entryTrampoline),
        (const char*, path),
        (const struct PPosixSpawnAttribs*, attr),
        (struct PThreadUserData*, threadData),
        (char* const *, argv),
        (char* const *, envp)
    )
)

// posix_spawnattr_XXX: POSIX requires returning the error number directly (not via errno).
// _SYSEPILOGUE_passthrough passes PErrorCode directly as the int return value.
PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, int, PErrorCode, __, posix_spawnattr_init,
    PARGS2((struct PPosixSpawnAttribs*, attr), (size_t, attrSize)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, int, PErrorCode, __, posix_spawnattr_destroy,
    PARGS1((struct PPosixSpawnAttribs*, attr)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, int, PErrorCode, , posix_spawnattr_getflags,
    PARGS2((const posix_spawnattr_t* __restrict, attr), (short* __restrict, flags)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, int, PErrorCode, , posix_spawnattr_setflags,
    PARGS2((posix_spawnattr_t*, attr), (short, flags)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, int, PErrorCode, , posix_spawnattr_getpgroup,
    PARGS2((const posix_spawnattr_t* __restrict, attr), (pid_t* __restrict, pgroup)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, int, PErrorCode, , posix_spawnattr_setpgroup,
    PARGS2((posix_spawnattr_t*, attr), (pid_t, pgroup)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, int, PErrorCode, , posix_spawnattr_getschedparam,
    PARGS2((const posix_spawnattr_t* __restrict, attr), (struct sched_param* __restrict, schedparam)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, int, PErrorCode, , posix_spawnattr_setschedparam,
    PARGS2((posix_spawnattr_t* __restrict, attr), (const struct sched_param* __restrict, schedparam)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, int, PErrorCode, , posix_spawnattr_getschedpolicy,
    PARGS2((const posix_spawnattr_t* __restrict, attr), (int* __restrict, schedpolicy)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, int, PErrorCode, , posix_spawnattr_setschedpolicy,
    PARGS2((posix_spawnattr_t*, attr), (int, schedpolicy)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, int, PErrorCode, , posix_spawnattr_getsigdefault,
    PARGS2((const posix_spawnattr_t* __restrict, attr), (sigset_t* __restrict, sigdefault)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, int, PErrorCode, , posix_spawnattr_setsigdefault,
    PARGS2((posix_spawnattr_t* __restrict, attr), (const sigset_t* __restrict, sigdefault)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, int, PErrorCode, , posix_spawnattr_getsigmask,
    PARGS2((const posix_spawnattr_t* __restrict, attr), (sigset_t* __restrict, sigmask)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, int, PErrorCode, , posix_spawnattr_setsigmask,
    PARGS2((posix_spawnattr_t* __restrict, attr), (const sigset_t* __restrict, sigmask)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode, , setpgid,
    PARGS2((pid_t, pid), (pid_t, pgid)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, pid_t, PSysRetPair, , getpgrp, PARGS0())

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, uid_t, PSysRetPair, , getuid, PARGS0())

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, gid_t, PSysRetPair, , getgid, PARGS0())

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode, , seteuid,
    PARGS1((uid_t, uid)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode, , setegid,
    PARGS1((gid_t, gid)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode, , fchdir,
    PARGS1((int, fd)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, pid_t, PSysRetPair, , wait,
    PARGS1((int*, status)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, pid_t, PSysRetPair, , waitpid,
    PARGS3((pid_t, pid), (int*, status), (int, options)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode, , waitid,
    PARGS4((idtype_t, idtype), (id_t, id), (siginfo_t*, infop), (int, options)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, pid_t, PSysRetPair,    _, getpid,
    PARGS0())

PEXPAND_SYSCALL_NORET(_SYSEPILOGUE_passthrough, void, void, _, exit,
    PARGS1((int, exitCode)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, __, sysconf,
    PARGS2((int, name), (long*, outValue)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,     __, reboot,
    PARGS1((BootMode, bootMode)))

/*
 * Signal functions
 */

 PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode, _, kill,
    PARGS2((pid_t, pid), (int, sig)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode, , raise,
    PARGS1((int, sigNum)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,   , thread_kill,
    PARGS2((thread_id, threadID), (int, signo)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,   , thread_sigqueue,
    PARGS3((thread_id, threadID), (int, signo), (union sigval, value)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode, , sigaction,
    PARGS3((int, sigNum), (const struct sigaction*, action), (struct sigaction*, outPrevAction)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, _sig_func_ptr, PSysRetPair,, signal,
    PARGS2((int, sigNum), (_sig_func_ptr, handler)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode, , sigsuspend,
    PARGS1((const sigset_t*, sigmask)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,   , thread_sigmask,
    PARGS3((int, how), (const sigset_t*, newSet), (sigset_t*, outOldSet)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_errorcode, int, PErrorCode, , sigpending,
    PARGS1((sigset_t*, outSet)))

/*
 * Handle object functions
 */

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , duplicate_handle,
    PARGS2((handle_id, handle), (handle_id*, outNewHandle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , delete_handle,
    PARGS1((handle_id, handle)))

/*
 * Semaphore functions
 */

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , semaphore_create,
    PARGS4((sem_id*, outHandle), (const char*, name), (clockid_t, clockID), (int, count)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , semaphore_duplicate,
    PARGS2((sem_id*, outNewHandle), (sem_id, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , semaphore_delete,
    PARGS1((sem_id, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , semaphore_create_public,
    PARGS6((sem_id*, outHandle), (const char*, name), (clockid_t, clockID), (int, flags), (mode_t, mode), (int, count)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , semaphore_unlink_public,
    PARGS1((const char*, name)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , semaphore_acquire,
    PARGS1((sem_id, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , semaphore_acquire_timeout_ns,
    PARGS2((sem_id, handle), (bigtime_t, timeout)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , semaphore_acquire_deadline_ns,
    PARGS2((sem_id, handle), (bigtime_t, deadline)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , semaphore_acquire_clock_ns,
    PARGS3((sem_id, handle), (clockid_t, clockID), (bigtime_t, deadline)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , semaphore_try_acquire,
    PARGS1((sem_id, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , semaphore_release,
    PARGS1((sem_id, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , semaphore_get_count,
    PARGS2((sem_id, handle), (int*, outCount)))

/*
 * Mutex functions
 */

 PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , mutex_create,
    PARGS4((sem_id*, outHandle), (const char*, name), (PEMutexRecursionMode, recursionMode), (clockid_t, clockID)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , mutex_duplicate,
    PARGS2((sem_id*, outNewHandle), (sem_id, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , mutex_delete,
    PARGS1((sem_id, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , mutex_lock,
    PARGS1((sem_id, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , mutex_lock_timeout_ns,
    PARGS2((sem_id, handle), (bigtime_t, timeout)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , mutex_lock_deadline_ns,
    PARGS2((sem_id, handle), (bigtime_t, deadline)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , mutex_lock_clock_ns,
    PARGS3((sem_id, handle), (clockid_t, clockID), (bigtime_t, deadline)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , mutex_try_lock,
    PARGS1((sem_id, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , mutex_unlock,
    PARGS1((sem_id, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , mutex_lock_shared,
    PARGS1((sem_id, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , mutex_lock_shared_timeout_ns,
    PARGS2((sem_id, handle), (bigtime_t, timeout)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , mutex_lock_shared_deadline_ns,
    PARGS2((sem_id, handle), (bigtime_t, deadline)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , mutex_lock_shared_clock_ns,
    PARGS3((sem_id, handle), (clockid_t, clockID), (bigtime_t, deadline)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , mutex_try_lock_shared,
    PARGS1((sem_id, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , mutex_islocked,
    PARGS1((sem_id, handle)))

/*
 * Condition variable functions
 */

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , condition_var_create,
    PARGS3((handle_id*, outHandle), (const char*, name), (clockid_t, clockID)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,     , condition_var_delete,
    PARGS1((handle_id, handle)))


PEXPAND_SYSCALL(_SYSEPILOGUE_cancelpnt, PErrorCode,  PErrorCode,  , condition_var_wait,
    PARGS2((handle_id, handle), (handle_id, mutexHandle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_cancelpnt, PErrorCode, PErrorCode,   , condition_var_wait_timeout_ns,
    PARGS3((handle_id, handle), (handle_id, mutexHandle), (bigtime_t, timeout)))

PEXPAND_SYSCALL(_SYSEPILOGUE_cancelpnt, PErrorCode, PErrorCode,   , condition_var_wait_deadline_ns,
    PARGS3((handle_id, handle), (handle_id, mutexHandle), (bigtime_t, deadline)))

PEXPAND_SYSCALL(_SYSEPILOGUE_cancelpnt, PErrorCode, PErrorCode,   , condition_var_wait_clock_ns,
    PARGS4((handle_id, handle), (handle_id, mutexHandle), (clockid_t, clockID), (bigtime_t, deadline)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,     , condition_var_wakeup,
    PARGS2((handle_id, handle), (int, threadCount)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,     , condition_var_wakeup_all,
    PARGS1((handle_id, handle)))


/*
 * Object wait group functions
 */

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , object_wait_group_create,
    PARGS2((handle_id*, outHandle), (const char*, name)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , object_wait_group_delete,
    PARGS1((handle_id, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , object_wait_group_add_object,
    PARGS3((handle_id, handle), (handle_id, objectHandle), (ObjectWaitMode, waitMode)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , object_wait_group_remove_object,
    PARGS3((handle_id, handle), (handle_id, objectHandle), (ObjectWaitMode, waitMode)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , object_wait_group_add_file,
    PARGS3((handle_id, handle), (int, fileHandle), (ObjectWaitMode, waitMode)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , object_wait_group_remove_file,
    PARGS3((handle_id, handle), (int, fileHandle), (ObjectWaitMode, waitMode)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , object_wait_group_clear,
    PARGS1((handle_id, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , object_wait_group_wait,
    PARGS4((handle_id, handle), (handle_id, mutexHandle), (void*, readyFlagsBuffer), (size_t, readyFlagsSize)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , object_wait_group_wait_timeout_ns,
    PARGS5((handle_id, handle), (handle_id, mutexHandle), (bigtime_t, timeout), (void*, readyFlagsBuffer), (size_t, readyFlagsSize)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , object_wait_group_wait_deadline_ns,
    PARGS5((handle_id, handle), (handle_id, mutexHandle), (bigtime_t, deadline), (void*, readyFlagsBuffer), (size_t, readyFlagsSize)))


/*
 * Message port functions
 */

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , message_port_create,
    PARGS3((port_id*, outHandle), (const char*, name), (int, maxCount)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , message_port_duplicate,
    PARGS2((port_id*, outNewHandle), (port_id, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , message_port_delete,
    PARGS1((port_id, handle)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , message_port_send,
    PARGS5((port_id, handle), (handler_id, targetHandler), (int32_t, code), (const void*, data), (size_t, length)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , message_port_send_timeout_ns,
    PARGS6((port_id, handle), (handler_id, targetHandler), (int32_t, code), (const void*, data), (size_t, length), (bigtime_t, timeout)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode,    , message_port_send_deadline_ns,
    PARGS6((port_id, handle), (handler_id, targetHandler), (int32_t, code), (const void*, data), (size_t, length), (bigtime_t, deadline)))


PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, ssize_t, PSysRetPair, , message_port_receive,
    PARGS5((port_id, handle), (handler_id*, targetHandler), (int32_t*, code), (void*, buffer), (size_t, bufferSize)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, ssize_t, PSysRetPair, , message_port_receive_timeout_ns,
    PARGS6((port_id, handle), (handler_id*, targetHandler), (int32_t*, code), (void*, buffer), (size_t, bufferSize), (bigtime_t, timeout)))

PEXPAND_SYSCALL(_SYSEPILOGUE_errno_sysretpair, ssize_t, PSysRetPair, , message_port_receive_deadline_ns,
    PARGS6((port_id, handle), (handler_id*, targetHandler), (int32_t*, code), (void*, buffer), (size_t, bufferSize), (bigtime_t, deadline)))


/*
 * Debug functions
 */

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, bool, bool, , is_debugger_attached,
    PARGS0())

/*
 * Misc functions
 */

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , digital_pin_set_direction,
    PARGS2((DigitalPinID, pinID), (DigitalPinDirection_e, dir)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , digital_pin_set_drive_strength,
    PARGS2((DigitalPinID, pinID), (DigitalPinDriveStrength_e, strength)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , digital_pin_set_pull_mode,
    PARGS2((DigitalPinID, pinID), (PinPullMode_e, mode)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , digital_pin_set_peripheral_mux,
    PARGS2((DigitalPinID, pinID), (DigitalPinPeripheralID, peripheral)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , digital_pin_read,
    PARGS2((DigitalPinID, pinID), (bool*, outValue)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , digital_pin_write,
    PARGS2((DigitalPinID, pinID), (bool, value)))


PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , write_backup_register,
    PARGS2((size_t, registerID), (uint32_t, value)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , read_backup_register,
    PARGS2((size_t, registerID), (uint32_t*, outValue)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, bool,       bool,       , has_nmi_status,
    PARGS0())

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , log_and_clear_nmi_status,
    PARGS0())

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , beep_seconds,
    PARGS1((float, duration)))


PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , system_log_register_category,
    PARGS5((uint32_t, categoryHash), (PLogChannel, channel), (const char*, categoryName), (const char*, displayName), (PLogSeverity, initialLogLevel)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , system_log_set_category_minimum_severity,
    PARGS2((uint32_t, categoryHash), (PLogSeverity, logLevel)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , system_log_is_category_active,
    PARGS3((uint32_t, categoryHash), (PLogSeverity, logLevel), (bool*, outIsActive)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , system_log_get_category_channel,
    PARGS2((uint32_t, categoryHash), (PLogChannel*, outChannel)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , system_log_get_severity_name,
    PARGS3((PLogSeverity, logLevel), (char*, buffer), (size_t, bufferLen)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , system_log_get_category_name,
    PARGS3((uint32_t, categoryHash), (char*, buffer), (size_t, bufferLen)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , system_log_get_category_display_name,
    PARGS3((uint32_t, categoryHash), (char*, buffer), (size_t, bufferLen)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , system_log_add_message,
    PARGS3((uint32_t, category), (PLogSeverity, severity), (const char*, message)))


PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , add_serial_command_handler,
    PARGS2((uint32_t, command), (port_id, messagePortID)))

PEXPAND_SYSCALL(_SYSEPILOGUE_passthrough, PErrorCode, PErrorCode, , serial_command_send_data,
    PARGS4((void*, header), (size_t, headerSize), (const void*, data), (size_t, dataSize)))


PEXPAND_SYSCALL_VOID(_SYSEPILOGUE_passthrough, void, void, , sigreturn,
    PARGS1((uint8_t*, stackPtr)))

#ifdef PEXPAND_SYSCALL_VOID_defined
#undef PEXPAND_SYSCALL_VOID
#undef PEXPAND_SYSCALL_VOID_defined
#endif

#ifdef PEXPAND_SYSCALL_NORET_defined
#undef PEXPAND_SYSCALL_NORET
#undef PEXPAND_SYSCALL_NORET_defined
#endif

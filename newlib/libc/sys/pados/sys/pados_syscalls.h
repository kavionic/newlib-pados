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
#include <PadOS/Threads.h>
#include <PadOS/ThreadLocal.h>
#include <PadOS/ObjectWaitGroup.h>
#include <PadOS/BootMode.h>
#include <PadOS/SyscallReturns.h>

#ifdef __cplusplus
extern "C" {
#endif

struct iovec;

typedef uint64_t PSysRetPair;

static_assert(sizeof(PSysRetPair) == 8);

#define SYS_open                                        0  
#define SYS_openat                                      1  
#define SYS_reopen_file                                 2  
#define SYS_close                                       3  
#define SYS_fcntl                                       4  
#define SYS_dup                                         5  
#define SYS_dup2                                        6  
#define SYS_rename                                      7  
#define SYS_fstat                                       8  
#define SYS_stat                                        9  
#define SYS_write_stat                                  10 
#define SYS_isatty                                      11 
#define SYS_seek                                        12 
#define SYS_read                                        13 
#define SYS_pread                                       14 
#define SYS_readv                                       15 
#define SYS_preadv                                      16 
#define SYS_write                                       17 
#define SYS_pwrite                                      18 
#define SYS_writev                                      19 
#define SYS_pwritev                                     20 
#define SYS_device_control                              21 
#define SYS_create_directory                            22 
#define SYS_read_directory                              23 
#define SYS_rewind_directory                            24 
#define SYS_remove_directory                            25 
#define SYS_unlink_file                                 26 
#define SYS_readlink                                    27 
#define SYS_symlink                                     28 
#define SYS_get_directory_path                          29 
#define SYS_chdir                                       30 
#define SYS_getcwd                                      31 
#define SYS_fsync                                       32 
#define SYS_mount                                       33 
#define SYS_get_monotonic_time_ns                       34 
#define SYS_get_monotonic_time_hires_ns                 35 
#define SYS_get_real_time_ns                            36 
#define SYS_get_real_time_hires_ns                      37 
#define SYS_set_real_time_ns                            38 
#define SYS_get_clock_time_offset_ns                    39 
#define SYS_get_clock_time_ns                           40 
#define SYS_get_clock_time_hires_ns                     41 
#define SYS_get_idle_time_ns                            42 
#define SYS_get_clock_resolution_ns                     43 
#define SYS_set_clock_resolution_ns                     44 
#define SYS_thread_attribs_init                         45 
#define SYS_thread_spawn                                46 
#define SYS_thread_terminate                            47 
#define SYS_thread_detach                               48 
#define SYS_thread_join                                 49 
#define SYS_get_thread_id                               50 
#define SYS_thread_set_priority                         51 
#define SYS_thread_get_priority                         52 
#define SYS_get_thread_info                             53 
#define SYS_get_next_thread_info                        54 
#define SYS_snooze_ns                                   55 
#define SYS_snooze_until_ns                             56 
#define SYS_yield                                       57 
#define SYS_thread_kill                                 58 
#define SYS_getpid                                      59 
#define SYS_kill                                        60 
#define SYS_get_dirty_disk_cache_blocks                 61
#define SYS_exit                                        62 
#define SYS_sysconf                                     63 
#define SYS_semaphore_create                            64 
#define SYS_semaphore_duplicate                         65 
#define SYS_semaphore_delete                            66 
#define SYS_semaphore_create_public                     67 
#define SYS_semaphore_unlink_public                     68 
#define SYS_semaphore_acquire                           69 
#define SYS_semaphore_acquire_timeout_ns                70 
#define SYS_semaphore_acquire_deadline_ns               71 
#define SYS_semaphore_acquire_clock_ns                  72 
#define SYS_semaphore_try_acquire                       73 
#define SYS_semaphore_release                           74 
#define SYS_semaphore_get_count                         75 
#define SYS_mutex_create                                76 
#define SYS_mutex_duplicate                             77 
#define SYS_mutex_delete                                78 
#define SYS_mutex_lock                                  79 
#define SYS_mutex_lock_timeout_ns                       80 
#define SYS_mutex_lock_deadline_ns                      81 
#define SYS_mutex_lock_clock_ns                         82 
#define SYS_mutex_try_lock                              83 
#define SYS_mutex_unlock                                84 
#define SYS_mutex_lock_shared                           85 
#define SYS_mutex_lock_shared_timeout_ns                86 
#define SYS_mutex_lock_shared_deadline_ns               87 
#define SYS_mutex_lock_shared_clock_ns                  88 
#define SYS_mutex_try_lock_shared                       89 
#define SYS_mutex_islocked                              90 
#define SYS_condition_var_create                        91 
#define SYS_condition_var_delete                        92 
#define SYS_condition_var_wait                          93 
#define SYS_condition_var_wait_timeout_ns               94 
#define SYS_condition_var_wait_deadline_ns              95 
#define SYS_condition_var_wait_clock_ns                 96 
#define SYS_condition_var_wakeup                        97 
#define SYS_condition_var_wakeup_all                    98 
#define SYS_reboot                                      99
#define SYS_object_wait_group_create                    100
#define SYS_object_wait_group_delete                    101
#define SYS_object_wait_group_add_object                102
#define SYS_object_wait_group_remove_object             103
#define SYS_object_wait_group_add_file                  104
#define SYS_object_wait_group_remove_file               105
#define SYS_object_wait_group_clear                     106
#define SYS_object_wait_group_wait                      107
#define SYS_object_wait_group_wait_timeout_ns           108
#define SYS_object_wait_group_wait_deadline_ns          109
#define SYS_message_port_create                         110
#define SYS_message_port_duplicate                      111
#define SYS_message_port_delete                         112
#define SYS_message_port_send                           113
#define SYS_message_port_send_timeout_ns                114
#define SYS_message_port_send_deadline_ns               115
#define SYS_message_port_receive                        116
#define SYS_message_port_receive_timeout_ns             117
#define SYS_message_port_receive_deadline_ns            118
#define SYS_get_total_irq_time_ns                       119
#define SYS_duplicate_handle                            120
#define SYS_delete_handle                               121
#define SYS_is_debugger_attached                        122
#define SYS_digital_pin_set_direction                   123
#define SYS_digital_pin_set_drive_strength              124
#define SYS_digital_pin_set_pull_mode                   125
#define SYS_digital_pin_set_peripheral_mux              126
#define SYS_digital_pin_read                            127
#define SYS_digital_pin_write                           128
#define SYS_write_backup_register                       129
#define SYS_read_backup_register                        130
#define SYS_beep_seconds                                131
#define SYS_system_log_register_category                132
#define SYS_system_log_set_category_minimum_severity    133
#define SYS_system_log_is_category_active               134
#define SYS_system_log_get_category_channel             135
#define SYS_system_log_get_severity_name                136
#define SYS_system_log_get_category_name                137
#define SYS_system_log_get_category_display_name        138
#define SYS_system_log_add_message                      139
#define SYS_add_serial_command_handler                  140
#define SYS_serial_command_send_data                    141
#define SYS_posix_spawn                                 142
#define SYS_sigaction                                   143
#define SYS_thread_sigqueue                             144
#define SYS_thread_sigmask                              145
#define SYS_raise                                       146
#define SYS_signal                                      147
#define SYS_sigsuspend                                  148
#define SYS_thread_cancel                               149
#define SYS_thread_setcancelstate                       150
#define SYS_thread_setcanceltype                        151
#define SYS_has_nmi_status                              152
#define SYS_log_and_clear_nmi_status                    153
#define SYS_posix_spawnattr_init                        154
#define SYS_posix_spawnattr_destroy                     155
#define SYS_posix_spawnattr_getflags                    156
#define SYS_posix_spawnattr_setflags                    157
#define SYS_posix_spawnattr_getpgroup                   158
#define SYS_posix_spawnattr_setpgroup                   159
#define SYS_posix_spawnattr_getschedparam               160
#define SYS_posix_spawnattr_setschedparam               161
#define SYS_posix_spawnattr_getschedpolicy              162
#define SYS_posix_spawnattr_setschedpolicy              163
#define SYS_posix_spawnattr_getsigdefault               164
#define SYS_posix_spawnattr_setsigdefault               165
#define SYS_posix_spawnattr_getsigmask                  166
#define SYS_posix_spawnattr_setsigmask                  167
#define SYS_setpgid                                     168
#define SYS_getuid                                      169
#define SYS_getgid                                      170
#define SYS_seteuid                                     171
#define SYS_setegid                                     172
#define SYS_fchdir                                      173
#define SYS_wait                                        174
#define SYS_waitpid                                     175
#define SYS_waitid                                      176
#define SYS_getpgrp                                     177
#define SYS_COUNT                                       178
// Syscalls process in the exception handler. Not present in the syscall table.
#define SYS_sigreturn                                   (SYS_COUNT + 0)
#define SYS_process_signals                             (SYS_COUNT + 1)
#define SYS_thread_exit                                 (SYS_COUNT + 2)

#define PEXPAND_SYSCALL(EPILOGUE, RETTYPE, RETTYPE_SYS, FPREFIX, FNAME, SIGNATURE) \
    RETTYPE_SYS __##FPREFIX##FNAME(PDECL_LIST(SIGNATURE)); \
    RETTYPE FPREFIX##FNAME(PDECL_LIST(SIGNATURE));

#define PEXPAND_SYSCALL_NORET(EPILOGUE, RETTYPE, RETTYPE_SYS, FPREFIX, FNAME, SIGNATURE) \
    __attribute__((noreturn)) RETTYPE FPREFIX##FNAME(PDECL_LIST(SIGNATURE));

#include <PadOS/SyscallDefinitions.h>

#undef PEXPAND_SYSCALL
#undef PEXPAND_SYSCALL_NORET

#ifdef __cplusplus
}
#endif

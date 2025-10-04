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

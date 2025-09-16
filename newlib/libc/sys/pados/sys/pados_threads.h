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

#include <sys/pados_types.h>

typedef void* (*ThreadEntryPoint_t)(void*);


typedef enum
{
    ThreadState_Running,
    ThreadState_Ready,
    ThreadState_Sleeping,
    ThreadState_Waiting,
    ThreadState_Zombie,
    ThreadState_Deleted
} ThreadState;

typedef enum
{
    PThreadDetachState_Detached,
    PThreadDetachState_Joinable
} PThreadDetachState;

struct _PThreadAttribs
{
    const char*         Name;
    int                 Priority;
    PThreadDetachState  DetachState;
    void*               StackAddress;
    size_t              StackSize;
    void*               ThreadLocalStorageAddress;
    size_t              ThreadLocalStorageSize;
};

#ifdef __cplusplus
struct PThreadAttribs : _PThreadAttribs
{
    PThreadAttribs(const char* name, int priority = 0, PThreadDetachState detachState = PThreadDetachState_Joinable, size_t stackSize = 0)
    {
        Name                        = name;
        Priority                    = priority;
        DetachState                 = detachState;
        StackAddress                = nullptr;
        StackSize                   = stackSize;
        ThreadLocalStorageAddress   = nullptr;
        ThreadLocalStorageSize      = 0;
    }
};
#else /* __cplusplus */
typedef struct _PThreadAttribs PThreadAttribs;
#endif /* __cplusplus */

typedef struct
{
    handle_id   ThreadID;
    handle_id   ProcessID;
    char        ProcessName[OS_NAME_LENGTH];
    char        ThreadName[OS_NAME_LENGTH];

    ThreadState State;		    // Current task state.
    uint32_t    Flags;
    handle_id   BlockingObject;	// The object we wait for, or INVALID_HANDLE.

    int         Priority;
    int         DynamicPri;
    bigtime_t   SysTimeNano;    //	Nanos in kernel mode.
    bigtime_t   UserTimeNano;   //	Nanos in user mode.
    bigtime_t   RealTimeNano;   //	Total nanos of execution.
    bigtime_t   QuantumNano;    //	Maximum allowed nanos of execution before preemption.

    void* Stack;
    size_t      StackSize;
} ThreadInfo;

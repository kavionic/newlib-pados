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

#ifdef __cplusplus
#define PCREAT_WAITMODE(NAME, ERRORCODE) NAME = ERRORCODE
enum class ObjectWaitMode : int
#else
#define PCREAT_WAITMODE(NAME, ERRORCODE) ObjectWaitMode_##NAME = ERRORCODE
typedef enum
#endif
{
    PCREAT_WAITMODE(Read,       0),
    PCREAT_WAITMODE(Write,      1),
    PCREAT_WAITMODE(ReadWrite,  2),
    PCREAT_WAITMODE(_SIZEEXTEND, 0x7fffffff)
}
#ifdef __cplusplus
;
#else
ObjectWaitMode;
#endif

#undef PCREAT_WAITMODE

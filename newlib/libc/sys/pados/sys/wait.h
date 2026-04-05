/*
 * Copyright (C) 2026 Kurt Skauen. All rights reserved.
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

#ifndef _SYS_WAIT_H
#define _SYS_WAIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/signal.h>


#define WNOHANG     0x00000001  /* Return immediately if there are no children to wait for. */
#define WSTOPPED    0x00000002  /* Status will be returned for any child that has stopped upon receipt of a signal. */
#define WEXITED     0x00000004  /* Wait for processes that have exited. */
#define WCONTINUED  0x00000008  /* Status will be returned for any child that was stopped and has been continued. */
#define WUNTRACED   WSTOPPED
#define WNOWAIT     0x01000000  /* Don't reap, just poll status.  */

/* A status looks like:
      <1 byte info> <1 byte code>

      <code> == 0, child has exited, info is the exit value
      <code> == 1..7e, child has exited, info is the signal number.
      <code> == 7f, child has stopped, info was the signal number.
      <code> == 80, there was a core dump.
*/
   
#define WIFEXITED(w)    (((w) & 0xff) == 0)
#define WIFSIGNALED(w)  (((w) & 0x7f) > 0 && (((w) & 0x7f) < 0x7f))
#define WIFSTOPPED(w)   (((w) & 0xff) == 0x7f)
#define WEXITSTATUS(w)  (((w) >> 8) & 0xff)
#define WTERMSIG(w)     ((w) & 0x7f)
#define WSTOPSIG        WEXITSTATUS

typedef enum
{
    P_ALL,
    P_PID,
    P_PGID
} idtype_t;

pid_t wait (int *);
pid_t waitpid (pid_t, int *, int);
int waitid(idtype_t idtype, id_t id, siginfo_t* infop, int options);


#ifdef _LIBC
pid_t _wait (int *);
#endif


#ifdef __cplusplus
};
#endif

#endif

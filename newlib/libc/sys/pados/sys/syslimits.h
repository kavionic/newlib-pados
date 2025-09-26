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

#ifndef _SYS_SYSLIMITS_H_
#define _SYS_SYSLIMITS_H_


//#define	AIO_LISTIO_MAX /* Maximum number of I / O operations in a single list I / O call supported by the implementation. */
//#define	AIO_MAX /* Maximum number of outstanding asynchronous I / O operations supported by the implementation. */
//#define	AIO_PRIO_DELTA_MAX 0 /* The maximum amount by which a process can decrease its asynchronous I / O priority level from its own scheduling priority. */
//#define	ARG_MAX 4096 /* Maximum length of argument to the exec functions including environment data. */
//#define	ATEXIT_MAX /* Maximum number of functions that may be registered with atexit(). */
#define	CHILD_MAX           256     /* Maximum number of simultaneous processes per real user ID. */
//#define	DELAYTIMER_MAX /* Maximum number of timer expiration overruns. */
//#define	HOST_NAME_MAX /* Maximum length of a host name(not including the terminating null) as returned from the gethostname() function. */
#define	IOV_MAX             1024    /* Maximum number of iovec structures that one process has available for use with readv() or writev(). */
//#define	LOGIN_NAME_MAX /* Maximum length of a login name. */
//#define	MQ_OPEN_MAX /* The maximum number of open message queue descriptors a process may hold. */
//#define	MQ_PRIO_MAX /*The maximum number of message priorities supported by the implementation. */
#define	OPEN_MAX            4096        /* Maximum number of files that one process can have open at any one time. */
#define	PAGESIZE            4096        /* Size in bytes of a page. */
#define	PAGE_SIZE           PAGESIZE    /* Equivalent to PAGESIZE. If either PAGESIZE or PAGE_SIZE is defined, the other is defined with the same value. */
//#define	PTHREAD_DESTRUCTOR_ITERATIONS /* Maximum number of attempts made to destroy a thread's thread-specific data values on thread exit. */
#define	PTHREAD_KEYS_MAX    64  /* Maximum number of data keys that can be created by a process. */
#define	PTHREAD_STACK_MIN   200 /* Minimum size in bytes of thread stack storage. */
//#define	PTHREAD_THREADS_MAX /* Maximum number of threads that can be created per process. */
#define	RE_DUP_MAX 255 /*The number of repeated occurrences of a BRE permitted by the regexec() and regcomp() functions when using the interval notation {\(m, n\}; see BREs Matching Multiple Characters. */
//#define	RTSIG_MAX /* Maximum number of realtime signals reserved for application use in this implementation. */
#define	SEM_NSEMS_MAX   4096    /* Maximum number of semaphores that a process may have. */
#define	SEM_VALUE_MAX   INT_MAX /* The maximum value a semaphore may have. */
//#define	SIGQUEUE_MAX /* Maximum number of queued signals that a process may send and have pending at the receiver(s) at any time. */
//#define	SS_REPL_MAX /* The maximum number of replenishment operations that may be simultaneously pending for a particular sporadic server scheduler. */
//#define	STREAM_MAX /* The number of streams that one process can have open at one time.If defined, it has the same value as FOPEN_MAX (see <stdio.h>). */
//#define	SYMLOOP_MAX /* Maximum number of symbolic links that can be reliably traversed in the resolution of a pathname in the absence of a loop. */
//#define	TIMER_MAX /* Maximum number of timers per process supported by the implementation. */
//#define	TRACE_EVENT_NAME_MAX /* Maximum length of the trace event name. */
//#define	TRACE_NAME_MAX /* Maximum length of the trace generation version string or of the trace stream name. */
//#define	TRACE_SYS_MAX /* Maximum number of trace streams that may simultaneously exist in the system. */
//#define	TRACE_USER_EVENT_MAX /*Maximum number of user trace event type identifiers that may simultaneously exist in a traced process, including the predefined user trace event POSIX_TRACE_UNNAMED_USER_EVENT. */
//#define	TTY_NAME_MAX /* Maximum length of terminal device name. */
//#define	TZNAME_MAX /* Maximum number of bytes supported for the name of a timezone(not of the TZ variable). 
//                    * Note: The length given by TZNAME_MAX does not include the quoting characters mentioned in Other Environment Variables. */
#define	FILESIZEBITS    64      /* Minimum number of bits needed to represent, as a signed integer value, the maximum size of a regular file allowed in the specified directory. */
#define	LINK_MAX        INT_MAX /* Maximum number of links to a single file. */
#define	MAX_CANON       255     /* Maximum number of bytes in a terminal canonical input line. */
#define	MAX_INPUT       255     /* Minimum number of bytes for which space is available in a terminal input queue; therefore, the maximum number of bytes a conforming application may require to be typed as input before reading them. */
#define	NAME_MAX        255     /* Maximum number of bytes in a filename(not including terminating null). */
#define	PATH_MAX        4096    /* Maximum number of bytes in a pathname, including the terminating null character. */
#define	PIPE_BUF        512     /* Maximum number of bytes that is guaranteed to be atomic when writing to a pipe. */
//#define	POSIX_ALLOC_SIZE_MIN /* Minimum number of bytes of storage actually allocated for any portion of a file. */
//#define	POSIX_REC_INCR_XFER_SIZE /* Recommended increment for file transfer sizes between the {POSIX_REC_MIN_XFER_SIZE} and {POSIX_REC_MAX_XFER_SIZE} values. */
//#define	POSIX_REC_MAX_XFER_SIZE /* Maximum recommended file transfer size. */
//#define	POSIX_REC_MIN_XFER_SIZE /* Minimum recommended file transfer size. */
//#define	POSIX_REC_XFER_ALIGN /* Recommended file transfer buffer alignment. */
#define	SYMLINK_MAX     PATH_MAX    /* Maximum number of bytes in a symbolic link. */


#define	BC_BASE_MAX         99      /* Maximum obase values allowed by the bc utility. */
#define	BC_DIM_MAX          2048    /* Maximum number of elements permitted in an array by the bc utility. */
#define	BC_SCALE_MAX        99      /* Maximum scale value allowed by the bc utility. */
#define	BC_STRING_MAX       1000    /* Maximum length of a string constant accepted by the bc utility. */
//#define	CHARCLASS_NAME_MAX /* Maximum number of bytes in a character class name. */
#define	COLL_WEIGHTS_MAX    0       /* Maximum number of weights that can be assigned to an entry of the LC_COLLATE order keyword in the locale definition file; see Locale. */
#define	EXPR_NEST_MAX       32      /* Maximum number of expressions that can be nested within parentheses by the expr utility. */
#define	LINE_MAX            2048    /* Unless otherwise noted, the maximum length, in bytes, of a utility's input line (either standard input or another file), when the utility is described as processing text files. The length includes room for the trailing <newline>. */
#define	NGROUPS_MAX         16      /* Maximum number of simultaneous supplementary group IDs per process. */

#endif

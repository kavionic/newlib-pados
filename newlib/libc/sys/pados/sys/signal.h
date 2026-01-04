/* sys/signal.h */

#ifndef _SYS_SIGNAL_H
#define _SYS_SIGNAL_H
#ifdef __cplusplus
extern "C" {
#endif

#include "_ansi.h"
#include <sys/cdefs.h>
#include <sys/features.h>
#include <sys/types.h>
#include <sys/_sigset.h>
#include <sys/_timespec.h>
#include <stdint.h>

#if !defined(_SIGSET_T_DECLARED)
#define _SIGSET_T_DECLARED
typedef __sigset_t sigset_t;
#endif


/* sigev_notify values
   NOTE: P1003.1c/D10, p. 34 adds SIGEV_THREAD.  */

#define SIGEV_NONE   1  /* No asynchronous notification shall be delivered */
                        /*   when the event of interest occurs. */
#define SIGEV_SIGNAL 2  /* A queued signal, with an application defined */
                        /*  value, shall be delivered when the event of */
                        /*  interest occurs. */
#define SIGEV_THREAD 3  /* A notification function shall be called to */
                        /*   perform notification. */

/*  Signal Generation and Delivery, P1003.1b-1993, p. 63
    NOTE: P1003.1c/D10, p. 34 adds sigev_notify_function and
          sigev_notify_attributes to the sigevent structure.  */

typedef union sigval
{
  int    sival_int;    /* Integer signal value */
  void  *sival_ptr;    /* Pointer signal value */
} sigval_t;

typedef struct sigevent
{
    sigval_t        sigev_value;    /* Signal value */
    int             sigev_signo;    /* Signal number */
    int             sigev_notify;   /* Notification type */
    void          (*sigev_notify_function)(sigval_t); /* Notification function */
    pthread_attr_t* sigev_notify_attributes; /* Notification attributes */
} sigevent_t;


/* Signal Actions, P1003.1b-1993, p. 64 */
/* si_code values, p. 66 */

#define SI_QUEUE    -1      /* Sent by sigqueue. */
#define SI_TIMER    -2      /* Sent by timer expiration. */
#define SI_MESGQ    -3      /* Sent by real time mesq state change (currently unimplemented). */
#define SI_ASYNCIO  -4      /* Sent by AIO completion (currently unimplemented). */
#define SI_USER     0       /* Sent by kill, raise, pthread_kill. */
#define SI_KERNEL   0x80    /* Sent by system. */

/* SIGILL */
#define ILL_ILLOPC  1       /* Illegal opcode. */
#define ILL_ILLOPN  2       /* Illegal operand. */
#define ILL_ILLADR  3       /* Illegal addressing mode. */
#define ILL_ILLTRP  4       /* Illegal trap. */
#define ILL_PRVOPC  5       /* Privileged opcode. */
#define ILL_PRVREG  6       /* Privileged register. */
#define ILL_COPROC  7       /* Co-processor error. */
#define ILL_BADSTK  8       /* Internal stack error. */

/* SIGFPE */
#define FPE_INTDIV  1       /* Integer divide by zero. */
#define FPE_INTOVF  2       /* Integer overflow. */
#define FPE_FLTDIV  3       /* Floating point divide by zero. */
#define FPE_FLTOVF  4       /* Floating point overflow. */
#define FPE_FLTUND  5       /* Floating point underflow. */
#define FPE_FLTRES  6       /* Floating point inexact result. */
#define FPE_FLTINV  7       /* Floating point invalid operation. */
#define FPE_FLTSUB  8       /* Subscript out of range. */

/* SIGSEGV */
#define SEGV_MAPERR 1       /* Address not mapped to object. */
#define SEGV_ACCERR 2       /* Invalid permissions for mapped object. */

/* SIGBUS */
#define BUS_ADRALN  1       /* Invalid address alignment.  */
#define BUS_ADRERR  2       /* Non-existent physical address.  */
#define BUS_OBJERR  3       /* Object specific hardware error.  */

/* SIGTRAP */
#define TRAP_BRKPT  1       /* Process breakpoint. */
#define TRAP_TRACE  2       /* Process trace trap. */

/* SIGCHLD */
#define CLD_EXITED      1   /* Child has exited. */
#define CLD_KILLED      2   /* Child was killed. */
#define CLD_DUMPED      3   /* Child terminated abnormally. */
#define CLD_TRAPPED     4   /* Traced child has trapped. */
#define CLD_STOPPED     5   /* Child has stopped. */
#define CLD_CONTINUED   6   /* Stopped child has continued. */


#define __SI_PAD_SIZE 31

typedef struct
{
    int     si_signo;   /* Signal number. */
    int     si_code;    /* Signal code. */
    pid_t   si_pid;     /* Sender's pid. */
    uid_t   si_uid;     /* Sender's uid. */
    int     si_errno;   /* The errno associated with signal. */

    __extension__ union
    {
        __uint32_t __pad[__SI_PAD_SIZE];    /* Make total size divisible by 8 and give some room for future growth. */
        __extension__ struct
        {
            __extension__ union
            {
                sigval_t si_sigval; /* Signal value. */
                sigval_t si_value;  /* Signal value. */
            };
            __extension__ struct
            {
                timer_t si_tid;             /* Timer id. */
                unsigned int si_overrun;    /* Overrun count. */
            };
        };
        /* SIGCHLD */
        __extension__ struct
        {
            int si_status;      /* Exit code. */
            clock_t si_utime;   /* User time. */
            clock_t si_stime;   /* System time. */
        };

        void* si_addr;  /* Faulting address for terminating signals. */
    };
} siginfo_t;



#define SA_NOCLDSTOP 1              /* Do not generate SIGCHLD when children stop */
#define SA_SIGINFO   2              /* Invoke the signal catching function with three arguments instead of one */
#define SA_RESTART   0x10000000     /* Restart syscall on signal return */
#define SA_ONSTACK   0x20000000     /* Call signal handler on alternate signal stack provided by sigaltstack(). */
#define SA_NODEFER   0x40000000     /* Don't automatically block the signal when its handler is being executed  */
#define SA_RESETHAND 0x80000000     /* Reset to SIG_DFL on entry to handler */
#define SA_ONESHOT   SA_RESETHAND   /* Historical linux name */
#define SA_NOMASK    SA_NODEFER     /* Historical linux name */


/* struct sigaction notes from POSIX:
 *
 *  (1) Routines stored in sa_handler should take a single int as
 *      their argument although the POSIX standard does not require this.
 *      This is not longer true since at least POSIX.1-2008
 *  (2) The fields sa_handler and sa_sigaction may overlap, and a conforming
 *      application should not use both simultaneously.
 */

typedef void (*_sig_func_ptr)(int);

typedef struct sigaction
{
  int         sa_flags;       /* Special flags to affect behavior of signal */
  sigset_t    sa_mask;        /* Additional set of signals to be blocked */
                              /*   during execution of signal-catching */
                              /*   function. */
  union
  {
    _sig_func_ptr _handler;  /* SIG_DFL, SIG_IGN, or pointer to a function */
    void      (*_sigaction)( int, siginfo_t *, void * );
  } _signal_handlers;
} sigaction_t;

#define sa_handler    _signal_handlers._handler
#define sa_sigaction  _signal_handlers._sigaction

/*
 * Minimum and default signal stack constants. Allow for target overrides
 * from <sys/features.h>.
 */
#ifndef MINSIGSTKSZ
#define MINSIGSTKSZ 2048
#endif
#ifndef SIGSTKSZ
#define SIGSTKSZ 8192
#endif

/*
 * Possible values for ss_flags in stack_t below.
 */
#define SS_ONSTACK  0x1
#define SS_DISABLE  0x2

/*
 * Structure used in sigaltstack call.
 */
typedef struct sigaltstack
{
  void     *ss_sp;    /* Stack base or pointer.  */
  int       ss_flags; /* Flags.  */
  size_t    ss_size;  /* Stack size.  */
} stack_t;

#define SIG_SETMASK 0   /* set mask with sigprocmask() */
#define SIG_BLOCK   1   /* set of signals to block */
#define SIG_UNBLOCK 2   /* set of signals to, well, unblock */

int sigprocmask(int, const sigset_t *, sigset_t *);

int pthread_sigmask(int, const sigset_t *, sigset_t *);

#ifdef _LIBC
int _kill(pid_t, int);
#endif /* _LIBC */

int kill(pid_t, int);

#if __BSD_VISIBLE || __XSI_VISIBLE >= 4
int killpg(pid_t, int);
#endif

int sigaction(int, const struct sigaction *, struct sigaction *);
int sigaddset(sigset_t *, const int);
int sigdelset(sigset_t *, const int);
int sigismember(const sigset_t *, int);
int sigfillset(sigset_t *);
int sigemptyset(sigset_t *);
int sigpending(sigset_t *);
int sigsuspend(const sigset_t *);
int sigwait(const sigset_t *, int *);


int sigpause(int);

int sigaltstack(const stack_t *__restrict, stack_t *__restrict);

int pthread_kill(pthread_t, int);

/*  3.3.8 Synchronously Accept a Signal, P1003.1b-1993, p. 76
    NOTE: P1003.1c/D10, p. 39 adds sigwait().  */

int sigwaitinfo(const sigset_t *, siginfo_t *);
int sigtimedwait(const sigset_t *, siginfo_t *, const struct timespec *);

/*  3.3.9 Queue a Signal to a Process, P1003.1b-1993, p. 78 */
int sigqueue(pid_t, int, const union sigval);


/* Using __MISC_VISIBLE until POSIX Issue 8 is officially released */
#if __MISC_VISIBLE

/* POSIX Issue 8 adds sig2str() and str2sig() */

#if __SIZEOF_INT__ >= 4
#define SIG2STR_MAX 17  /* (sizeof("RTMAX+") + sizeof("4294967295") - 1) */
#else
#define SIG2STR_MAX 12  /* (sizeof("RTMAX+") + sizeof("65535") - 1) */
#endif

int sig2str(int, char *);
int str2sig(const char *__restrict, int *__restrict);

#endif /* __MISC_VISIBLE */


#define SIGHUP      1   /* hangup */
#define SIGINT      2   /* interrupt */
#define SIGQUIT     3   /* quit */
#define SIGILL      4   /* illegal instruction (not reset when caught) */
#define SIGTRAP     5   /* trace trap (not reset when caught) */
#define SIGABRT     6   /* used by abort, replace SIGIOT in the future */
#define SIGIOT      SIGABRT /* Obsolete signal for PDP-11 IOT instruction. Replaced by SIGABRT. */
#define SIGEMT      7   /* EMT instruction */
#define SIGFPE      8   /* floating point exception */
#define SIGKILL     9   /* kill (cannot be caught or ignored) */
#define SIGBUS      10  /* bus error */
#define SIGSEGV     11  /* segmentation violation */
#define SIGSYS      12  /* bad argument to system call */
#define SIGPIPE     13  /* write on a pipe with no one to read it */
#define SIGALRM     14  /* alarm clock */
#define SIGTERM     15  /* software termination signal from kill */

#define SIGURG      16  /* urgent condition on IO channel */
#define SIGSTOP     17  /* sendable stop signal not from tty */
#define SIGTSTP     18  /* stop signal from tty */
#define SIGCONT     19  /* continue a stopped process */
#define SIGCHLD     20  /* to parent on child stop or exit */
#define SIGCLD      20  /* System V name for SIGCHLD */
#define SIGTTIN     21  /* to readers pgrp upon background tty read */
#define SIGTTOU     22  /* like TTIN for output if (tp->t_local&LTOSTOP) */
#define SIGIO       23  /* input/output possible signal */
#define SIGPOLL     SIGIO   /* System V name for SIGIO */
#define SIGPROF     27  /* profiling timer expired */
#define SIGWINCH    28  /* window changed */
#define SIGPWR      29  /* power failure (System V) */
#define SIGUSR1     30  /* user defined signal 1 */
#define SIGUSR2     31  /* user defined signal 2 */

/* Real-Time Signals Range, P1003.1b-1993, p. 61
   NOTE: By P1003.1b-1993, this should be at least RTSIG_MAX
         (which is a minimum of 8) signals.
 */
#define SIGRTMIN 32
#define SIGRTMAX 63
#define __SIGFIRSTNOTRT SIGHUP
#define __SIGLASTNOTRT  SIGUSR2

#define NSIG    32      /* signal 0 implied */
#define NRTSIG  32


#ifdef __cplusplus
}
#endif


#ifndef _SIGNAL_H_
/* Some applications take advantage of the fact that <sys/signal.h>
 * and <signal.h> are equivalent in glibc.  Allow for that here.  */
#include <signal.h>
#endif
#endif /* _SYS_SIGNAL_H */

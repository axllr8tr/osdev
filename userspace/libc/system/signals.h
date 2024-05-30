#ifndef _SIGNALS_H
#define _SIGNALS_H

// based on Linux signals

#define SIGEXIT   0
#define SIGHUP    1  // hangup
#define SIGINT    2  // interrupt
#define SIGQUIT   3  // quit
#define SIGILL    4  // illegal instruction
#define SIGTRAP   5  // debug
#define SIGABRT   6  // abort   
#define SIGIOT    6
#define SIGBUS    7  // bus error
#define SIGFPE    8  // float error
#define SIGKILL   9  // kill
#define SIGUSR1   10 // user-defined 1 
#define SIGSEGV   11 // segfault
#define SIGUSR2   12 // user-defined 2
#define SIGPIPE   13 // broken pipe
#define SIGALRM   14 // alarm
#define SIGTERM   15 // terminate
#define SIGSTKFLT 16 // stack fault
#define SIGCHLD   17 // child gone
#define SIGCONT   18 // back to work
#define SIGSTOP   19 // have a break
#define SIGTSTP   20 // ^Z
#define SIGTTIN   21 // job control in
#define SIGTTOU   22 // job control out
#define SIGURG    23 // something something urgent data
#define SIGXCPU   24 // out of cpu time
#define SIGXFSZ   25 // file too big
#define SIGVTALRM 26 // tty alarm
#define SIGPROF   27 // profiling
#define SIGWINCH  28 // window size changed
#define SIGPOLL   29 // pollable event
#define SIGPWR    30 // power management
#define SIGSYS    31 // syscall args bad

static const char *signal_strings[] = {
  "Hangup",
  "Interrupt",
  "Quit",
}

#endif /* SIGNALS_H */

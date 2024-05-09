#include "../include/defs.h"
#include "syscalls.h"
#include "../video/video.h"
#include "../baseio/printf.h"
#include "../tty/tty_print.h"
#include "../utils/io_ports.h"
#include "../cpu/interrupts.h"
#include "../logging/log.h"

volatile u32 syscall_amount = 0; // huh

typedef int (*syscall_t)(); // requires a cast

static int kwrite(int fd, const void *data, size_t limit) {
  switch (fd) {
    case 0 : { // stdout
      tprint((const char *)data); // temporary
      break;
    }
    case 1 : { // stderr
      tprint("\033[31m"); // red text
      tprint((const char *)data);
      tprint("\033[0m"); // reset
      break;
    }
    default : {
      kdebug_log(ERROR "write: write to fd %i is not implemented", fd);
    }
  }
  limit = limit;
  return 0;
}

static int kinst_irq(u8 irq_no, const irq_handler_t handler) {
  irq_handler_install(irq_no, handler);
  return 0;
}

syscall_t syscalls[255]; 

static int ksyscall_install(syscall_t call, u32 idx) {
  syscalls[idx] = call;
  return 0;
}

int ksyscall_install_full() {
  ksyscall_install(kwrite, syscall_amount++);
  ksyscall_install((syscall_t)kinst_irq, syscall_amount++); // HACK: apparently func() is not just any number of args
  kdebug_log(INFO "installed %u system calls", syscall_amount);
  return 0;
}

int ksyscall(u32 eax, u32 ebx, u32 ecx, u32 edx) {
  syscall_t desired_syscall = syscalls[eax];
  if (!desired_syscall) {
    kdebug_log(ERROR "nonexistent syscall %u was called", eax);
    return -1;
  }
  int ret = 0x00;
  asm volatile (
    "push %1\n"
    "push %2\n"
    "push %3\n"
    "call *%4\n"
    "pop %%ebx\n"
    "pop %%ebx\n"
    "pop %%ebx\n"
    : "=a" (ret) : "r" (edx), "r" (ecx), "r" (ebx), "r" (desired_syscall)
  );
  if (eax != 0) kdebug_log(DEBUG "syscall %u was called, returned %i", eax, ret); // else recursion occurs
  return ret;
}



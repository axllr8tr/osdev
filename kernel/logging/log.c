#include "log.h"
#include "../include/defs.h"
#include "../baseio/printf.h"
#include <stdarg.h>

u8 last_msg_prio = PRIO_WARN; // assume last message was a warning if no loglevel was provided
u8 min_loglevel = PRIO_DEBUG;

#define END_LOG "\033[0m\n"

void kdebug_log(const char *message, ...) {
  if (message[0] == '\xff' && message[1] && message[1] <= 9) {
    last_msg_prio = (u8)message[1];
    message += 2;
  } else {
    last_msg_prio = PRIO_WARN;
  }
  va_list ap;
  va_start(ap, message);


  switch (last_msg_prio * (last_msg_prio >= min_loglevel)) {
    case PRIO_DEBUG : {
      kprintf_c("\033[38;5;8m[k] debug: ");
      kvprintf_c((char *)message, ap);
      kprintf_c(END_LOG);
      break;
    }

    case PRIO_INFO : {
      kprintf_c("\033[38;5;12m[k] info: ");
      kvprintf_c((char *)message, ap);
      kprintf_c(END_LOG);
      break;
    }

    case PRIO_NOTICE : {
      kprintf_c("\033[38;5;6m[k] notice: ");
      kvprintf_c((char *)message, ap);
      kprintf_c(END_LOG);
      break;
    }

    case PRIO_WARN : {
      kprintf_c("\033[1;33m[k] warning: ");
      kvprintf_c((char *)message, ap);
      kprintf_c(END_LOG);
      break;
    }

    case PRIO_ERROR : {
      kprintf_c("\033[38;5;9m[k] error: ");
      kvprintf_c((char *)message, ap);
      kprintf_c(END_LOG);
      break;
    }

    case PRIO_CRIT : {
      kprintf_c("\033[38;5;1m[k] critical: ");
      kvprintf_c((char *)message, ap);
      kprintf_c(END_LOG);
      break;
    }

    case PRIO_EMERG : {
      kprintf_c("\033[38;5;1m[k] emergency: ");
      kvprintf_c((char *)message, ap);
      kprintf_c(END_LOG);
      break;
    }

    case PRIO_SPANIC : {
      kprintf_c("\033[38;5;15m\033[48;5;1m[k] panic: ");
      kvprintf_c((char *)message, ap);
      kprintf_c(END_LOG);
      while (true)
        asm volatile ("hlt");
      break;
    }

    default:
      break;
  }
  va_end(ap);
}

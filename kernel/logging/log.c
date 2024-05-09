#include "log.h"
#include "../include/defs.h"
#include "../baseio/printf.h"
#include <stdarg.h>

u8 last_msg_prio = PRIO_WARN; // assume last message was a warning if no loglevel was provided
u8 min_loglevel = PRIO_INFO;

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
      kprintf_c("\033[38;5;8mdebug: ");
      kvprintf_c((char *)message, ap);
      kprintf_c(END_LOG);
      break;
    }

    case PRIO_INFO : {
      kprintf_c("\033[38;5;12minfo: ");
      kvprintf_c((char *)message, ap);
      kprintf_c(END_LOG);
      break;
    }

    case PRIO_NOTICE : {
      kprintf_c("\033[38;5;6mnotice: ");
      kvprintf_c((char *)message, ap);
      kprintf_c(END_LOG);
      break;
    }

    case PRIO_WARN : {
      kprintf_c("\033[1;33mwarning: ");
      kvprintf_c((char *)message, ap);
      kprintf_c(END_LOG);
      break;
    }

    case PRIO_ERROR : {
      kprintf_c("\033[38;5;9merror: ");
      kvprintf_c((char *)message, ap);
      kprintf_c(END_LOG);
      break;
    }
    default:
      break;
  }
  va_end(ap);
}

#include "log.h"
#include "../include/defs.h"
#include "../baseio/printf.h"
#include <stdarg.h>

static const char *mesg_levels[] = {
  "what", // cannot just happen as '\x00' is a string terminator
  "debug",
  "info",
  "notice",
  "warning",
  "error",
  "critical",
  "alert",
  "emergency",
  "non-halting panic"
};

static const char *mesg_colors[] = {
  "\033[48;15;38;0m",
  "\033[38;5;8m",
  "\033[38;5;7m",
  "\033[38;5;6m",
  "\033[1;33m",
  "\033[38;5;9m",
  "\033[38;5;1m",
  "\033[38;5;9;48;8m",
  "\033[38;5;7;41m",
  "\033[31;5;41m",
};

u8 default_prio = PRIO_WARN;
u8 last_msg_prio = PRIO_WARN;
u8 min_loglevel = PRIO_INFO;

#define END_LOG "\033[0m\n"

void kdebug_log(const char *message, ...) {
  if (message[0] == '\xff' && message[1] && message[1] <= 9) {
    last_msg_prio = (u8)message[1];
    message += 2;
  } else {
    last_msg_prio = default_prio;
  }
  va_list ap;
  va_start(ap, message);


  switch (last_msg_prio * (last_msg_prio >= min_loglevel)) {
    case PRIO_DEBUG...PRIO_SPANIC : {
      kprintf_c("%skernel: %s: ", mesg_colors[last_msg_prio], mesg_levels[last_msg_prio]);
      kvprintf_c((char *)message, ap);
      kprintf_c(END_LOG);
      break;
    }

    default:
      break;
  }
  va_end(ap);
}

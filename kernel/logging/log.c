#include "log.h"
#include "../include/defs.h"
#include "../baseio/printf.h"
#include <stdarg.h>

u8 last_msg_prio = 0xff; // 0xff = none


void kdebug_log(const char *message, ...) {
  if (message[0] == '\xff' && message[1] && message[1] <= 9) {
    last_msg_prio = (u8)message[1];
    message += 2;
  } else {
    last_msg_prio = 0xff;
  }
  va_list ap;
  va_start(ap, message);


  switch (last_msg_prio) {
    case PRIO_WARN : {
      kprintf("\033[1;33m");
      kvprintf((char *)message, ap);
    }
  }


  va_end(ap);
}

/* Formatted print function implementation */ 
#include "../include/strings.h"
#include "../include/defs.h"
#include <stdarg.h>
#include "printf.h"
#include "uprint.h"
#include "../string/conv.h"
#include "../system/syscalls.h"

#define SLIM_OR_LIM(U) (lim - ou_idx >= U) ? U : (lim - ou_idx)
#define ISERR(U) (U == -1) ? true : false

char global_buf[65536] = {0}; // 64KiB ought to be enough


void k_vsnprintf(char *buf, size_t lim, const char *fmt, va_list ap) {
  // buf: the buffer where the final string will be put
  // lim: max length of fmt
  // fmt: string to be formatted 
  // va:  argument vector thing
  
  size_t ou_idx = 0;
  
  while (*fmt && ou_idx < lim) {
    if (*fmt != '%') {
      buf[ou_idx++] = *fmt;
      fmt++;
      continue;
    } else {
      fmt++;
    }
    switch (*fmt) {

      case 'b' : {
        ou_idx += itoa_exbuf_k(buf + ou_idx, SLIM_OR_LIM(8), va_arg(ap, u32), 2, false);
        fmt++;
        break;
      }

      case 'u' : {
        ou_idx += itoa_exbuf_k(buf + ou_idx, SLIM_OR_LIM(10), va_arg(ap, u32), 10, false);
        fmt++;
        break;
      }

      case 'i' : {
        ou_idx += itoa_exbuf_s_k(buf + ou_idx, SLIM_OR_LIM(10), va_arg(ap, i32), 10, false);
        fmt++;
        break;
      }
      
      case 'x' : {
        ou_idx += itoa_exbuf_k(buf + ou_idx, SLIM_OR_LIM(8), va_arg(ap, u32), 16, false);
        fmt++;
        break;
      }

      case 'X' : {
        ou_idx += itoa_exbuf_k(buf + ou_idx, SLIM_OR_LIM(8), va_arg(ap, u32), 16, true);
        fmt++;
        break;
      }

      case 's' : {
        char *str = va_arg(ap, char*);
        while(*str) {
          buf[ou_idx++] = *str++;
        }
        fmt++;
        break;
      }

      case 'c' : {
        char chr = va_arg(ap, int);
        buf[ou_idx++] = chr & 0xff; // for safety
        fmt++;
        break;
      }

      case 'B' : {
        int a = va_arg(ap, int);
        buf[ou_idx++] = a ? 't' : 'f';
        fmt++;
        break;
      }

      case '!' : {
        uprint(va_arg(ap, char*));
        fmt++;
        break;
      }

      default : {
        buf[ou_idx++] = *fmt;
        fmt++;
        break;
      }
    }
  }
  buf[ou_idx] = 0; // string terminator
}

void kvsnprintf_(char *buf, size_t lim, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  k_vsnprintf(buf, lim, fmt, ap);
  va_end(ap);
}

void kvprintf(const char *fmt, va_list ap) {
  k_vsnprintf(global_buf, 65536, fmt, ap);
  ksyscall(0, 0, (u32)global_buf, 65536);
}

void kprintf(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  kvprintf(fmt, ap);
  va_end(ap);
}

static const u8 vga_to_ansi_offs[] = {
  0, 
  4,
  2, 
  6,
  1,
  5,
  3,
  7,
  8, 
  12,
  10, 
  14,
  9,
  13,
  11,
  15,
};

void kcvprintf(u8 col, const char *fmt, va_list ap) { // NOTE: compatibility purposes

  // set fg
  kprintf("\033[38;5;%um", vga_to_ansi_offs[col & 0xf]);

  // set bg
  kprintf("\033[48;5;%um", vga_to_ansi_offs[(col >> 4) & 0xf]);

  // print like any other string
  kvprintf(fmt, ap);

}
void kcprintf(u8 col, const char *fmt, ...) { // NOTE: compatibility purposes
  va_list ap;
  va_start(ap, fmt);

  kcvprintf(col, fmt, ap);

  va_end(ap);
}


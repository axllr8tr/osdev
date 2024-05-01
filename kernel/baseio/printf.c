/* Formatted print function implementation */ 
#include "../include/strings.h"
#include "../include/defs.h"
#include <stdarg.h>
#include "printf.h"
#include "uprint.h"

#define SLIM_OR_LIM(U) (lim - ou_idx >= U) ? U : (lim - ou_idx)
#define ISERR(U) (U == -1) ? true : false

char global_buf[65536] = {0}; // 64KiB ought to be enough

int _utoa(char *buf, u8 lim, u32 num, u8 base, bool uppercase) { 
  
  char *lc = "0123456789abcdef";
  char *uc = "0123456789ABCDEF";
  char *chrs = uppercase ? uc : lc;

  u32 nm = num;
  u8 idx0 = 1; // \0 should be at the start of _buf_rev[65] since it will be reversed!
               // side-effect: debugging will require &_buf_rev[1] to be provided
  u8 idx1 = 0;

  char _buf_rev[65] = {0};

  if (!base || base > 16) { 
    return -1; 
  }

  for (u8 i = 0; i < lim; i++) {
    buf[i] = 0;
  } // cleanup

  do {
    u32 rem = nm % base;
    nm /= base;
    _buf_rev[idx0] = chrs[rem];
    idx0++;
  } while (nm != 0);

  while (_buf_rev[--idx0] && idx1 < lim) { // omagah!
    buf[idx1] = _buf_rev[idx0];
    idx1++;  // ^^ still ok i suppose since buf was initialized beforehand (wow im smart)
  }
  return idx1;

}

void _vsnprintf(char *buf, size_t lim, const char *fmt, va_list ap) {
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
        ou_idx += _utoa(buf + ou_idx, SLIM_OR_LIM(8), va_arg(ap, u32), 2, false);
        fmt++;
        break;
      }

      case 'u' : {
        ou_idx += _utoa(buf + ou_idx, SLIM_OR_LIM(10), va_arg(ap, u32), 10, false);
        fmt++;
        break;
      }
      
      case 'x' : {
        ou_idx += _utoa(buf + ou_idx, SLIM_OR_LIM(8), va_arg(ap, u32), 16, false);
        fmt++;
        break;
      }

      case 'X' : {
        ou_idx += _utoa(buf + ou_idx, SLIM_OR_LIM(8), va_arg(ap, u32), 16, true);
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

void vsnprintf_(char *buf, size_t lim, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  _vsnprintf(buf, lim, fmt, ap);
  va_end(ap);
}

void printf(char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  _vsnprintf(global_buf, 65536, fmt, ap);
  uprintc(global_buf, default_color);
  va_end(ap);
}

void cprintf(u8 col, char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  _vsnprintf(global_buf, 65536, fmt, ap);
  uprintc(global_buf, col);
  va_end(ap);
}


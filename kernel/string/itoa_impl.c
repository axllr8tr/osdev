#include "../include/defs.h"

// impl moved from baseio/printf.c! //
int itoa_exbuf_k(char *buf, size_t lim, u32 num, u8 base, bool uppercase) { 
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

int itoa_exbuf_s_k(char *buf, size_t lim, i32 num, u8 base, bool uppercase) { 
  char *lc = "0123456789abcdef";
  char *uc = "0123456789ABCDEF";
  char *chrs = uppercase ? uc : lc;

  u32 nm = num;
  u8 idx0 = 1; // \0 should be at the start of _buf_rev[65] since it will be reversed!
               // side-effect: debugging will require &_buf_rev[1] to be provided
  u8 idx1 = 0;

  bool negative = false;

  if (num < 0) { 
    negative = true;
    nm *= -1;
  }

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

  _buf_rev[idx0] = negative ? '-' : '\0';

  while (_buf_rev[--idx0] && idx1 < lim) { // omagah!
    buf[idx1] = _buf_rev[idx0];
    idx1++;  // ^^ still ok i suppose since buf was initialized beforehand (wow im smart)
  }


  return idx1;
}

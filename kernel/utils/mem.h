#ifndef _MEM_H
#define _MEM_H

#include "../include/defs.h"

extern inline void memcpy(u8 *__restrict dest, const u8 *__restrict src, size_t n) {
  for(; n > 0; n--) {
    dest[n] = src[n]; // backwards, but should be ok
  }
}

extern inline void memcpyw(u16 *__restrict dest, const u16 *__restrict src, size_t n) {
  size_t idx = 0;
  for(; idx < n; idx++) {
    dest[idx] = src[idx]; // backwards, but should be ok
  }
}

extern inline void memfillw(u16 *__restrict dest, const u16 val, size_t n) {
  for(; n > 0; n--) {
    dest[n] = val;
  }
}



#endif /* _MEM_H */

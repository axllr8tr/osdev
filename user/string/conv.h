#ifndef _ITOA_IMPL_H
#define _ITOA_IMPL_H

#include "../include/defs.h"

int itoa_exbuf(char *buf, size_t lim, u32 num, u8 base, bool uppercase);
u32 atoi(char *src);
u32 atoi_b(char *src, u8 base);

#endif /* _ITOA_IMPL_H */

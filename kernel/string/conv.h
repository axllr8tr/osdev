#ifndef _ITOA_IMPL_H
#define _ITOA_IMPL_H

#include "../include/defs.h"

int itoa_exbuf_k(char *buf, size_t lim, u32 num, u8 base, bool uppercase);
int atoi_k(char *src);

#endif /* _ITOA_IMPL_H */

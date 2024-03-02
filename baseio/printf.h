#ifndef __PRINTF_H
#define __PRINTF_H

#include "../include/defs.h"

extern void _vsnprintf(char *, size_t, const char *, va_list);
extern void vsnprintf_(char *, size_t, const char *, ...);

#endif /* __PRINTF_H */

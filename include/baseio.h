#ifndef __BASEIO_H
#define __BASEIO_H

#include "defs.h"

/* uprint = unformatted print */
void uprint(char *str);
void uprintc(char *str, unsigned char col);

int _sprintf(char *buff, char *fmt, va_list ap);
int printf(char *fmt, ...);

#endif /* __BASEIO_H */

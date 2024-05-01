#ifndef __STRINGS_H
#define __STRINGS_H

#include "defs.h"

extern i8 strcmp(const char *l, const char *r);
extern char *strchr(const char *s, int c);
extern u32 strlen(const char *s);
extern char *strcat(char *dest, const char *src);
extern i8 strcpy(char *src, char *dest);

#endif /* __STRINGS_H */

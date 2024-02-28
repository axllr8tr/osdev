#ifndef _BASEIO_UPRINT
#define _BASEIO_UPRINT

#include "../include/defs.h" // types

extern u8 default_color;

void uprint(char *s);        // Basic null-terminated string, default color will be used
void uprintc(char *s, u8 c); // Basic null-terminated string, color from 2nd argument will be used 

#endif /* _BASEIO_UPRINT */

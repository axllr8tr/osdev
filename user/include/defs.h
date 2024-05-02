#ifndef __DEFS_H
#define __DEFS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;

typedef char* i8p;
typedef unsigned char* u8p;
typedef short* i16p;
typedef unsigned short* u16p;
typedef int* i32p;
typedef unsigned int* u32p;
typedef long long* i64p;
typedef unsigned long long* u64p;


typedef struct eiframe {
  u32 gs, fs, es, ds;
  u32 esi, edi, ebp, esp, ebx, edx, ecx, eax;
  u32 vector;
  u32 err;
  u32 eip, cs, eflags;
  u32 iret_esp, iret_ss;
} __attribute__((packed)) x86_extended_interrupt_frame_t;

typedef void (*irq_handler_t)(x86_extended_interrupt_frame_t*);

#endif /* __DEFS_H */

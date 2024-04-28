#ifndef _GDT_H
#define _GDT_H

#include "../include/defs.h"

typedef struct sdesc {
  u16 limit_low;
  u16 base_low;
  u8 base_mid;
  u8 access;
  u8 lim_high_flags;
  u8 base_high;
} __attribute__((packed)) gdt_segment_descriptor_t;

typedef struct gdtptr {
  u16 limit;
  u32 base;
} __attribute__((packed)) gdt_descriptor_pointer_t;

void gdt_setup_flat();
extern void gdt_deploy_flat();

#endif /* _GDT_H */

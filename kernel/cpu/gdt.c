#include "gdt.h"
#include "../include/defs.h"

gdt_descriptor_pointer_t global_gdt_pointer;
gdt_segment_descriptor_t global_gdt[6];

static void gdt_gen_entry(gdt_segment_descriptor_t *dest, u32 base, u32 limit, u8 access, u8 flags) {
  dest->limit_low = limit & 0xffff;
  dest->base_low = base & 0xffff;
  dest->base_mid = (base >> 16) & 0xff;
  dest->access = access;
  dest->lim_high_flags = (flags << 4) | ((limit >> 16) & 0xf);
  dest->base_high = base >> 24;
}

void gdt_setup_flat() {
  global_gdt_pointer.base = (u32)&global_gdt[0];
  global_gdt_pointer.limit = (sizeof(gdt_segment_descriptor_t) * 5) - 1;
  gdt_gen_entry(&global_gdt[0], 0, 0, 0, 0); // null descriptor
  gdt_gen_entry(&global_gdt[1], 0, 0xfffff, 0x9a, 0xc); // kernel code
  gdt_gen_entry(&global_gdt[2], 0, 0xfffff, 0x92, 0xc); // kernel data
  gdt_gen_entry(&global_gdt[3], 0, 0xfffff, 0xfa, 0xc); // user code
  gdt_gen_entry(&global_gdt[4], 0, 0xfffff, 0xf2, 0xc); // user data
  // TODO: TSS
}

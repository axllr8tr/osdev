#include "../include/baseio.h"
#include "panic.h"
#include "../video/video.h"
#include "../baseio/printf.h"

static void halt() {
  asm inline ("hlt");
}

// invoke_panic(...) is invoked with panic(msg) and cpanic(code, msg) macros
// do not invoke manually as this defeats the whole purpose of these args!!!!
void invoke_panic(u32 code, char *file, const char *scope, int line, char *msg) {
  vga_fill_screen(vga_gen_entry(' ', 0x55)); // purple void
  x = 0; y = 0;
  kcprintf(0x5f, "\nPanic!\n");
  if (code) kcprintf(0x5f, "Error code: 0x%x\n", code);
  kcprintf(0x5f, "\nIn file %s on line %u in function %s: %s\n", file, line, scope, msg);
  kcprintf(0x5f, "\nThat's about it. Staying here until hardware reset.");
  // printf("%s", "oranges");
  halt();
}

void hcf(x86_extended_interrupt_frame_t *iframe) {
  x = 0; y = 0;
  kcprintf(0x4f, "Halted! v=%x e=%x\n", iframe->vector, iframe->err);
  kcprintf(0x4f, "eax %x ebx %x ecx %x edx %x\n", iframe->eax, iframe->ebx, iframe->ecx, iframe->edx);
  kcprintf(0x4f, "ebp %x esp %x eflags %x\n", iframe->ebp, iframe->esp, iframe->eflags);
  kcprintf(0x4f, "cs %x ds %x es %x fs %x gs %x\n", iframe->cs, iframe->ds, iframe->es, iframe->fs, iframe->gs);
  while (true)
    asm volatile ("hlt");
}

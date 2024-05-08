#include "8042_ps2.h"
#include "../utils/io_ports.h"

u32 ps2d_receive_data(void) {
  return inl(0x60);
}

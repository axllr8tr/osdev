#ifndef _8042_PS2_H
#define _8042_PS2_H

#include "../include/defs.h"

void ps2c_send_command(u8);
u32  ps2d_receive_data(void);

#endif /* _8042_PS2_H */

#ifndef __LLHW_H
#define __LLHW_H

#include "defs.h"

u8 ps2c_sendCmd(u8, bool nbr, u8);
u32 ps2d_sendCmd(u8, bool, u8);
u32 ps2d_recvKeyInput(void);

void crtc_reset(void);
void crtc_issueCommand(u16, u8, u8);

void pic_init(void);
void pic_disable(void);
void pic_sendEoi(u32);

void pit_init(u32);

typedef struct x86_32_iframe {
    uint32_t di, si, bp, sp, bx, dx, cx, ax; 
    uint32_t ds, es, fs, gs;                        
    uint32_t vector;                                 
    uint32_t err_code;                                
    uint32_t ip, cs, flags;                            
    uint32_t user_sp, user_ss;                          
} x86_iframe_t;


#endif /* __LLHW_H */

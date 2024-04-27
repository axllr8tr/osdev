#ifndef _PCI_HEADER_H
#define _PCI_HEADER_H

#include "../include/defs.h"

#define PCI_COMMAND_INT_DISABLE     1<<10 // interrupt disable, rw
#define PCI_COMMAND_FAST_B2B        1<<9  // fast back-to-back, ro
#define PCI_COMMAND_SERRNO          1<<8  // serr# enable, rw
#define PCI_COMMAND_PARITY_ERR_RESP 1<<6  // parity error responses, rw
#define PCI_COMMAND_VGA_PAL_SNOOP   1<<5  // vga pallet snooping, ro 
#define PCI_COMMAND_MEM_WINVALIDATE 1<<4  // memory write and invalidate, ro 
#define PCI_COMMAND_SPECIAL_CYCLES  1<<3  // special cycle monitoring, ro
#define PCI_COMMAND_BUS_MASTER      1<<2  // device can behave as bus master, rw 
#define PCI_COMMAND_MEMORY_SPACE    1<<1  // access to memory space, rw
#define PCI_COMMAND_IO_SPACE        1<<0  // access to i/o space, rw

#define PCI_STATUS_PARITY_ERROR     1<<15 // device detected a parity error, resettable
#define PCI_STATUS_SERRNO           1<<14 // device asserted a serr#, resettable
#define PCI_STATUS_MASTER_ABORT     1<<13 // master terminated xaction with master-abort, resettable
#define PCI_STATUS_TARGET_ABORT     1<<12 // master terminated xaction with target-abort, resettable
#define PCI_STATUS_TARGET_ABORT_SIG 1<<11 // target terminated xaction with target-abort, resettable
#define PCI_STATUS_DEVSEL_TIMING_1  1<<10 // i dunno, ro 
#define PCI_STATUS_DEVSEL_TIMING_2  1<<9  // i dunno, ro 
#define PCI_STATUS_MASTER_PERRNO    1<<8  // bus agent asserted perr# on a write operation and it was also a master, resettable 
#define PCI_STATUS_FAST_B2B_CAPABLE 1<<7  // fast back-to-back transaction capability, ro
#define PCI_STATUS_DOUBLE_CLOCK     1<<5  // device can run at 66 MHz clock speed, ro
#define PCI_STATUS_CAPABILITY_LIST  1<<4  // ptr for new capabilities linked list at offs 0x34, ro
#define PCI_STATUS_INTERRUPT        1<<3  // state of intX# signal; only works if ints are enabled, ro

#define PCI_HEADER_TYPE_GENERAL_DEV 0x0  // general device
#define PCI_HEADER_TYPE_PCI_TO_PCI  0x1  // pci-to-pci
#define PCI_HEADER_TYPE_PCI_TO_CBUS 0x2  // pci-to-cardbus
#define PCI_HEADER_MULTIFUNCTIONAL  1<<7 // multi-functional device

#define PCI_BIST_CAPABLE     1<<7 // device is capable of bist
#define PCI_BIST_STARTED     1<<6 // bist has started
#define PCI_BIST_COMP_CODE_1 1<<3 // all
#define PCI_BIST_COMP_CODE_2 1<<2 //    should
#define PCI_BIST_COMP_CODE_3 1<<1 //          be
#define PCI_BIST_COMP_CODE_4 1<<0 //            zero if nothing went wrong

#define PCI_DEVICE_CLASS_UNCLASSIFIED          0x00
#define PCI_DEVICE_CLASS_MASS_STORAGE          0x01
#define PCI_DEVICE_CLASS_NETWORK_CONTROLLER    0x02
#define PCI_DEVICE_CLASS_VIDEO_ADAPTER         0x03
#define PCI_DEVICE_CLASS_MULTIMEDIA            0x04
#define PCI_DEVICE_CLASS_MEMORY_CONTROLLER     0x05
#define PCI_DEVICE_CLASS_BRIDGE                0x06
#define PCI_DEVICE_CLASS_SIMPLE_COMMS          0x07
#define PCI_DEVICE_CLASS_BASE_PERIPHERAL       0x08
#define PCI_DEVICE_CLASS_INPUT_CONTROLLER      0x09
#define PCI_DEVICE_CLASS_DOCKING_STATION       0x0a
#define PCI_DEVICE_CLASS_PROCESSOR             0x0b
#define PCI_DEVICE_CLASS_SERIAL_CONTROLLER     0x0c
#define PCI_DEVICE_CLASS_WIRELESS_CONTROLLER   0x0d
#define PCI_DEVICE_CLASS_I2O_CONTROLLER        0x0e // not too intelligent, eh?
#define PCI_DEVICE_CLASS_SATELLITE_COMMS       0x0f
#define PCI_DEVICE_CLASS_ENCRYPTION_CONTROLLER 0x10 
#define PCI_DEVICE_CLASS_DSP_CONTROLLER        0x11
#define PCI_DEVICE_CLASS_COMPUTE_ACCELERATOR   0x12
#define PCI_DEVICE_CLASS_INSTRUMENTATION       0x13
#define PCI_DEVICE_CLASS_COPROCESSOR           0x40
#define PCI_DEVICE_CLASS_VENDOR_SPECIFIC       0xff

typedef struct pci_header_common {
  union {
    u32 reg0;
    struct {
      u16 vendor_id;
      u16 device_id;
    };
  };
  union {
    u32 reg1;
    struct {
      u16 status;
      u16 command;
    };
  };
  union {
    u32 reg2;
    struct {
      u8 device_class;
      u8 device_subclass;
      u8 iface;
      u8 revision;
    };
  };
  union {
    u32 reg3;
    struct {
      u8 bist;
      u8 header_type;
      u8 latency_clock;
      u8 cacheline_size;
    };
  };
} pci_header_common_t;

// i am sorry that i have put so many unions
// but that might kinda help in the future when i'm debugging stuff

typedef struct pci_header_general_device {
  pci_header_common_t common_header;
  union {
    u32 reg4;
    u32 bar0;
  };
  union {
    u32 reg5;
    u32 bar1;
  };
  union {  
    u32 reg6;
    u32 bar2;
  };
  union {
    u32 reg7;
    u32 bar3;
  };
  union {
    u32 reg8;
    u32 bar4;
  };
  union {
    u32 reg9;
    u32 bar5;
  };
  union {
    u32 rega; 
    u32 cis_pointer; 
  };
  union {
    u32 regb;
    struct {
      u16 sybsys_id;
      u16 subsys_ven_id;
    }; 
  };
  union {
    u32 regc;
    u32 xrom_base_addr;
  };
  union {
    u32 regd;
    struct {
      u8 resv0;
      u8 resv1;
      u8 resv2;
      u8 caps_pointer;
    };
  };
  union {
    u32 rege;
    struct {
      u8 resv3;
      u8 resv4;
      u8 resv5;
      u8 resv6;
    };
  };
  union {
    u32 regf;
    struct {
      u8 max_latency;
      u8 min_grant;
      u8 int_pin;
      u8 int_line;
    };
  };
} pci_header_general_device_t;

typedef struct pci_header_pci_to_pci {
  pci_header_common_t common_header;
  union {
    u32 reg4;
    u32 bar0;
  };
  union {
    u32 reg5;
    u32 bar1;
  };
  union {  
    u32 reg6;
    struct {
      u8 sec_latency;
      u8 sub_bus_no;
      u8 sec_bus_no;
      u8 pri_bus_no;
    };
  };
  union {
    u32 reg7;
    struct {
      u16 sec_status;
      u8 io_limit;
      u8 io_base;
    };
  };
  union {
    u32 reg8;
    struct {
      u16 mem_limit;
      u16 mem_base;
    };
  };
  union {
    u32 reg9;
    struct {
      u16 prefetch_mem_limit;
      u16 prefetch_mem_base;
    };
  };
  union {
    u32 rega; 
    u32 prefetch_base_upper32;
  };
  union {
    u32 regb;
    u32 prefetch_limit_upper32;
  };
  union {
    u32 regc;
    struct {
      u16 io_limit_upper16;
      u16 io_base_upper16;
    };
  };
  union {
    u32 regd;
    struct {
      u8 resv0;
      u8 resv1;
      u8 resv2;
      u8 caps_pointer;
    };
  };
  union {
    u32 rege;
    u32 xrom_base_addr;
  };
  union {
    u32 regf;
    struct {
      u16 bridge_control;
      u8 int_pin;
      u8 int_line;
    };
  };
} pci_header_pci_to_pci_t;

#endif /* _PCI_HEADER_H */

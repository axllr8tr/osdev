#ifndef _CPUID_H_LOC
#define _CPUID_H_LOC

#include "../include/defs.h"
#include <cpuid.h>

#define CPUID_VENDOR_INFO       0
#define CPUID_PROC_INFO         1
#define CPUID_CACHE_INFO        2
#define CPUID_CPU_CORE_ENUM     4
#define CPUID_PROC_BRAND_STR_P1 0x80000002
#define CPUID_PROC_BRAND_STR_P2 0x80000003
#define CPUID_PROC_BRAND_STR_P3 0x80000004

void cpuid_get_vendor(char *);
void cpuid_get_brand_string(char *);

#endif /* _CPUID_H_LOC */

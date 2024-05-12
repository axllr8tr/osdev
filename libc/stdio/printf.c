// printf(const char *, ...) for the userspace
// i thought it was kinda not ok calling kernel functions from userspace and NOT using syscalls for that purpose
// there's a reason for separation of kernelspace and userspace, right?
// so yeah, that is that

#include "../defs.h"

#define DEFAULT_OUTPUT(u) puts(u) // will execute write(stdout, u, strlen(u)) syscall
                                  // which is actually syscall(0, 0, u, strlen(u))



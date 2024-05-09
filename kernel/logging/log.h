#define DEBUG     "\xff\001"
#define INFO      "\xff\002"
#define NOTICE    "\xff\003"
#define WARNING   "\xff\004"
#define ERROR     "\xff\005"
#define CRITICAL  "\xff\006"
#define ALERT     "\xff\007"
#define EMERGENCY "\xff\010"
#define SOFTPANIC "\xff\011"

#define PRIO_DEBUG  1
#define PRIO_INFO   2
#define PRIO_NOTICE 3
#define PRIO_WARN   4
#define PRIO_ERROR  5
#define PRIO_CRIT   6
#define PRIO_ALERT  7
#define PRIO_EMERG  8
#define PRIO_SPANIC 9


void kdebug_log(const char *message, ...);

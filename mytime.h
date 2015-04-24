#include <time.h>
#include <sys/time.h>
#include <stdio.h>
 
#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

#define MIL_MILLONES 1E9

void current_utc_time(struct timespec *ts);

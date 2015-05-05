#include <time.h>

int
nanosleep (const struct timespec *rqtp, struct timespec *rmtp)
{
  unsigned long ret = (44 * (rqtp->tv_sec * 1000000 + rqtp->tv_nsec / 1000) - 32)/16;
  while(ret-- > 0) {
    asm ("nop");
  }
  return 0;
}

#include <unistd.h>

int
usleep (useconds_t useconds)
{
	int ret = (5*44 * useconds - 32)/(2*16);
  while(ret-- > 0) {
    asm ("nop");
  }
  return 0;
}

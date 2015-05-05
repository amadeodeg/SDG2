#include <unistd.h>

int
usleep (useconds_t useconds)
{
  while(useconds-- > 0) {
    asm ("nop");
  }
  return 0;
}

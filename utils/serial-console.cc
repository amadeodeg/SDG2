extern "C" {
#include <sys/types.h>
#include <sys/select.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
}
#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstdlib>

static int
serial_open (const char* dev, const char* speed_str, const char* mode_str,
	     bool hwf, bool swf)
{
  int fd = open (dev, O_RDWR | O_NOCTTY | O_NONBLOCK);
  if (fd < 0) {
    return -1;
  }

  int bit = mode_str[0];
  int par = mode_str[1];
  int stopb = mode_str[2];

  struct termios tty;
  tcgetattr(fd, &tty);

  speed_t speed;
  switch (atoi(speed_str)) {
  case 300:	speed = B300;	 break;
  case 600:	speed = B600;	 break;
  case 1200:	speed = B1200;	 break;
  case 2400:	speed = B2400;	 break;
  case 4800:	speed = B4800;	 break;
  case 9600:	speed = B9600;	 break;
  case 19200:	speed = B19200;	 break;
  case 38400:	speed = B38400;	 break;
  case 57600:	speed = B57600;	 break;
  case 115200:	speed = B115200; break;
  default:	speed = B0;	 break;
  }

  cfsetospeed (&tty, speed);
  cfsetispeed (&tty, speed);

  switch (bit) {
  case '5':
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS5;
    break;
  case '6':
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS6;
    break;
  case '7':
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS7;
    break;
  case '8':
  default:
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    break;
  }
  /* Set into raw, no echo mode */
  tty.c_iflag =  IGNBRK;
  tty.c_lflag = 0;
  tty.c_oflag = 0;
  tty.c_cflag |= CLOCAL | CREAD;
  tty.c_cflag &= ~CRTSCTS;
  tty.c_cc[VMIN] = 1;
  tty.c_cc[VTIME] = 5;

  if (swf)
    tty.c_iflag |= IXON | IXOFF;
  else
    tty.c_iflag &= ~(IXON|IXOFF|IXANY);

  tty.c_cflag &= ~(PARENB | PARODD);
  if (par == 'E')
    tty.c_cflag |= PARENB;
  else if (par == 'O')
    tty.c_cflag |= (PARENB | PARODD);

  if (stopb == '2')
    tty.c_cflag |= CSTOPB;
  else
    tty.c_cflag &= ~CSTOPB;

  if (hwf)
    tty.c_cflag |= CRTSCTS;
  else
    tty.c_cflag &= ~CRTSCTS;

  tcsetattr(fd, TCSANOW, &tty);
  return fd;
}

class Buffer {
  char data[1024*1024];
  char* prd;
  char* pwr;
 public:
  Buffer () : prd(data), pwr(data) {
  }
  int add (const char* buf) {
    int cnt = ::strlen(buf);
    memcpy (prd, buf, cnt);
    prd += cnt;
    return cnt;
  }
  int read (int fd) {
    int cnt = ::read (fd, prd, sizeof(data) - (prd - data));
    if ((cnt < 0) && (errno != EAGAIN))
      return -1;
    else if (cnt > 0)
      prd += cnt;
      return cnt;
    return 0;
  }
  int write (int fd) {
    int cnt = ::write (fd, pwr, prd - pwr);
    pwr += cnt;
    if (pwr >= prd)
      prd = pwr = data;
    else {
      int len = prd - pwr;
      memmove (data, pwr, len);
      pwr = data;
      prd = data + len;
    }
    return cnt;
  }
  int size () { return prd - pwr; }
};

static Buffer buf[2];

int
main (int argc, char* argv[])
{
  const char* device = "/dev/ttyS0";
  const char* speed = "19200";
  const char* mode = "8N1";
  const char* load = 0;
  const char* start = "20000";
  bool quiet = false;

  int opt;
  while ((opt = getopt (argc, argv, "d:l:m:qs:S:")) > 0) {
    switch (opt) {
    case 'd': device = optarg; break;
    case 'l': load = optarg; break;
    case 'm': mode = optarg; break;
    case 'q': quiet = true; break;
    case 's': speed = optarg; break;
    case 'S': start = optarg; break;
    default:
      std::cerr << "Unknown option `" << char(opt) << "'\n";
      exit (1);
    }
  }

  int s = serial_open (device, speed, mode, false, false);
  if (s < 0) {
    std::cerr << "Could not open " << argv[1] << "\n";
    exit (1);
  }

  char* env_timeout = getenv("TIMEOUT");
  int timeout = env_timeout? atoi (env_timeout) : 5000;

  if (load) {
    char line[1024];
    std::ifstream f(load);
    buf[0].add("\rdl\r");
    while (f.getline(line, 1024))
      buf[0].add(line);
    buf[0].add("go ");
    buf[0].add(start);
    buf[0].add("\r");
  }

  while (1) {
    fd_set rdset;
    FD_ZERO (&rdset);
    if (!quiet)
      FD_SET (0, &rdset);
    FD_SET (s, &rdset);
    fd_set wrset;
    FD_ZERO (&wrset);
    if (buf[1].size()) FD_SET (1, &wrset);
    if (buf[0].size()) FD_SET (s, &wrset);
    int ret;
    if (timeout > 0) {
      timeval tv = { timeout / 1000, timeout % 1000 };
      ret = select (s + 1, &rdset, &wrset, NULL, &tv);
      if (ret == 0)
	exit (0);
    }
    else {
      ret = select (s + 1, &rdset, &wrset, NULL, NULL);
    }
    if (ret > 0) {
      if (!quiet && FD_ISSET (0, &rdset))
	buf[0].read(0);
      if (FD_ISSET (s, &rdset))
	buf[1].read(s);
      if (FD_ISSET (1, &wrset))
	buf[1].write(1);
      if (FD_ISSET (s, &wrset))
	buf[0].write(s);
    }
  }
  return 0;
}

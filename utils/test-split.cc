#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
extern "C" {
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
}

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::string;

int
main ()
{
  mkdir ("out", 0777);

  char buf[1024];
  ofstream os ("out/BEGIN.txt");
  while (cin.getline(buf, 1024)) {
    if (buf[strlen(buf)-1] == '\r')
      buf[strlen(buf)-1] = '\0';
    if (strncmp(buf, ">>>>>>>>>>", 10) == 0) {
      os.close();
      string fname = string("out/") + (buf + 10) + ".txt";
      os.open(fname.c_str());
      continue;
    }
    os << buf << endl;
  }
  os.close();
  return 0;
}

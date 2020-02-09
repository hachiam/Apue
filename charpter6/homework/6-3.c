#include <sys/utsname.h>

#include "apue.h"

int main() {
  struct utsname utsBuf;

  if (uname(&utsBuf) < 0) err_msg("uname error!");

  printf("operating name is: %s\n", utsBuf.sysname);
  printf("name of this node: %s\n", utsBuf.nodename);
  printf("release name is: %s\n", utsBuf.release);
  printf("version name is: %s\n", utsBuf.version);
  printf("machine name is: %s\n", utsBuf.machine);

  exit(0);
}

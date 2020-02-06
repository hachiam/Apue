#include <fcntl.h>

#include "apue.h"

int main() {
  struct stat stabuf;

  /*turn on set-groupID, and turn off group excute*/
  if (stat("foo", &stabuf) < 0) printf("stat error for foo");
  if (chmod("foo", (stabuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
    printf("chmod error for foo");

  // set absolute mode to 'rw-r--r--'
  if (chmod("foo", S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP))
    printf("chmod error for foo");

  exit(0);
}

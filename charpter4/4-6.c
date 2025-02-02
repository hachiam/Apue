#include <fcntl.h>
#include <utime.h>

#include "apue.h"

int main(int argc, char *argv[]) {
  int i, fd;
  struct stat statbuf;
  struct utimbuf timebuf;

  for (i = 1; i < argc; i++) {
    if (stat(argv[i], &statbuf) < 0) {  // fetch current time
      printf("stat %s error", argv[i]);
      continue;
    }

    if ((fd = open(argv[i], O_RDONLY | O_TRUNC)) < 0) {  // truncate
      printf("open file %s error", argv[i]);
      continue;
    }
    close(fd);
    timebuf.actime = statbuf.st_atime;
    timebuf.modtime = statbuf.st_mtime;
    if (utime(argv[i], &timebuf) < 0) {
      printf("utime %s error", argv[i]);
      continue;
    }
  }

  exit(0);
}

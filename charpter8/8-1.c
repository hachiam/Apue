#include "apue.h"

int glob = 6;
char buf[] = "a write to stdout\n";

int main() {
  int var;
  pid_t pid;

  var = 88;

  if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
    err_sys("write error");
  printf("before fork\n");  // we don't flush stdout

  // fork()有两个返回值，子进程返回0,返回子进程id到父进程。
  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) {  // chird
    glob++;
    var++;
  } else {  // parent
    sleep(2);
  }
  printf("pid = %d, glob=%d, var= %d\n", getpid(), glob, var);

  exit(0);
}

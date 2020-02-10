#include "apue.h"

// vfork实例
int glob = 6;

int main() {
  int var;
  pid_t pid;

  var = 88;

  printf("before vfork\n");  // we don't flush stdout

  if ((pid = vfork()) < 0) {
    err_sys("vfork error");
  } else if (pid == 0) {  // chird
    glob++;
    var++;
    _exit(0);  //_exit()退出，不会清理标准io流
  }
  // parent continue here
  printf("pid = %d, glob=%d, var= %d\n", getpid(), glob, var);

  exit(0);
}

//eval a shell program
#include <iostream>
#include <sys/wait.h>
#include "apue.h"

int main(int argc, char *argv[])
{
  pid_t pid;
  if ((pid = fork()) < 0)
    err_quit("fork error");
  else if (pid == 0)
    if (execl("./hello.sh", NULL) < 0)
      err_quit("execl error");

  if (waitpid(pid, NULL, 0)<0) {
    err_sys("waitpid error");
  }
  return 0;
}


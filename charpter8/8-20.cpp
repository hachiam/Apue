#include "apue.h"
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  pid_t pid;

  if ((pid = fork()) < 0)
    err_quit("fork error");
  else if (pid == 0) {
    if(execl("./awkexample", "testinginterp", "myargl")<0)
      err_sys("execl error");
  }
  if (waitpid(pid, NULL, 0) < 0)
    err_sys("waitpid error");
  return 0;
}


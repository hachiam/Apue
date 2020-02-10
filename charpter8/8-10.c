#include <sys/wait.h>

#include "apue.h"

int main() {
  pid_t pid;

  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) {
    if (execl("/bin/ls", "ls", "-a", "-l", "-h") < 0) err_sys("execl error");
  }

  if (waitpid(pid, NULL, 0) < 0) err_sys("waitpid error");

  exit(0);
}

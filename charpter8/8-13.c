#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>

#include "apue.h"

int system(const char *cmdstring) {
  pid_t pid;
  int status;

  if (cmdstring == NULL) {
    return (1);  // always a command proccessor with unix
  }

  if ((pid = fork()) < 0) {
    status = -1;
  } else if (pid == 0) {
    execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
    _exit(127);  // execl error
  } else {
    while (waitpid(pid, &status, 0) < 0) {
      if (errno != EINTR) {
        status = -1;  // error other than EINTR from waitpid()
        break;
      }
    }
  }
  return (status);
}

int main() {
  int status;
  if ((status = system("date")) < 0) err_sys("system(), error");
  if ((status = system("ls -l > bar"))) err_sys("system(), error");

  exit(0);
}

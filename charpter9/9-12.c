#include "apue.h"
#include <errno.h>

static void
sig_hup(int signo) {
  printf("SIGHUP received, pid = %ld\n", (long)getpid());
}

static void
pr_ids(char *name) {
  printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n",
	 name, (long)getpid(), (long)getppid(), (long)getpgrp(),
	 (long)tcgetpgrp(STDIN_FILENO));
  fflush(stdout);
}

int main(int argc, char *argv[])
{
  char c;
  pid_t pid;

  pr_ids("parents");
  if((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid > 0) { //parents
    sleep(5); 
  } else {
    pr_ids("child");
    signal(SIGHUP, sig_hup); //establish signal handler
    kill(getpid(), SIGTSTP); // stop ourself
    pr_ids("child"); //print only if we're continued
    if (read(STDIN_FILENO, &c, 1) != 1)
      printf("read error %d on controlling TTY\n", errno);
  }
  return 0;
}

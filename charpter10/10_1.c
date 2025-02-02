#include "apue.h"

static void sig_usr(int);
int main() {
  if (signal(SIGUSR1, sig_usr) == SIG_ERR)
    err_sys("can't catch SIGusr1");
  if (signal(SIGUSR2, sig_usr) == SIG_ERR)
    err_sys("can't catch SIGusr2");

  for (;;)
    pause();
  
}

static void sig_usr(int signo) {
  if (signo == SIGUSR1) {
    printf("received SIGUSR1\n");
  }
  else if (signo == SIGUSR2) {
    printf("received SIGusr2");
  }
  else{
    err_dump("received %s\n", signo);
  }
}

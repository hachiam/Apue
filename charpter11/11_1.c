#include "apue.h"
#include <pthread.h>

pthread_t ntid;

void printntids(const char* s) {
  pid_t pid;
  pthread_t tid;

  pid = getpid();
  tid = pthread_self();
  printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid, (unsigned int)tid,
	 (unsigned int)tid);
}

void *
thr_fn(void *arg) {
  printntids("new thread: ");
  return ((void*)0);
}

int main() {
  int err;
  err = pthread_create(&ntid, NULL, thr_fn, NULL);
  if (err != 0) {
    err_quit("can't create thread: %s\n", strerror(err));
  }
  printntids("main thread");
  sleep(1);
  return 0;
}

#include "apue.h"

// iso规定一个进程可以登记32个函数,这些登记的函数将由exit自动调用。我们称其为终止处理程序，即exit
// handler 下面例子使用atexit函数来登记这些函数.
static void my_exit1(void);
static void my_exit2(void);

int main() {
  if (atexit(my_exit2) != 0) err_sys("can't register my_exit2\n");

  if (atexit(my_exit1) != 0) err_sys("can't register my_exit1\n");
  if (atexit(my_exit1) != 0) err_sys("can't register my_exit1\n");

  printf("main is done\n");

  return 0;
}

static void my_exit1() { printf("first exit handler\n"); }

static void my_exit2() { printf("second exit handler\n"); }

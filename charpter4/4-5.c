#include <fcntl.h>

#include "apue.h"

/*
 * unlink
 * 经常被用于处理程序崩溃，进程open或create创建新文件，然后立即掉哟你unlink。
 * 因为该文件是打开的，所以内容不ui被删除，知道进程终止。
 * */
int main() {
  if (open("foo", O_RDONLY) < 0) printf("open file foo error");

  if (unlink("foo") < 0) printf("unlink file foo error");
  printf("unlinked file\n");
  sleep(15);
  printf("done\n");
  exit(0);
}

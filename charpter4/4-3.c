#include "apue.h"
#include "fcntl.h"

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

/*
 * umask 用于屏蔽相关权限.
 * 要让创建的文件所有用户都能读写，那么先运行umask(0)
 */

int main() {
  umask(0);
  if (creat("foo", RWRWRW) < 0) printf("creat file foo error");
  umask(S_IRGRP | S_IROTH | S_IWGRP | S_IWOTH);
  if (creat("bar", RWRWRW) < 0) printf("creat file bar error");

  exit(0);
}

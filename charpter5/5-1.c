#include "apue.h"

//复制标准输入到标准输出，一次一个字符版本.
int main() {
  int n;

  while ((n = getc(stdin)) != EOF)
    if (putc(n, stdout) == EOF) err_sys("output error!\n");
  if (ferror(stdin)) err_sys("input error!");

  exit(0);
}

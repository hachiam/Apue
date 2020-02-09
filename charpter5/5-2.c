#include "apue.h"

//复制标准输入到标准输出，每次一行版本.
// fgets, fputs函数实现.
int main() {
  char buf[MAXLINE];

  while (fgets(buf, MAXLINE, stdin) != NULL)
    if (fputs(buf, stdout) == EOF) printf("output error!\n");
  if (ferror(stdin)) printf("input error!");

  exit(0);
}

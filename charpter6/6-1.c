#include <pwd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// getpwnam函数的一种实现.
struct passwd *getpwnam(const char *name) {
  struct passwd *ptr;
  setpwent();

  while ((ptr = getpwent()) != NULL)
    if (strcmp(name, ptr->pw_name) == 0) break;
  endpwent();

  return (ptr);
}

//测试函数
int main(int argc, char *argv[]) {
  if (argc != 2) printf("usage: a.out <username>");
  printf("UserName: %s\n", getpwnam(argv[1])->pw_name);
  printf("UserPasswd: %s\n", getpwnam(argv[1])->pw_passwd);
  printf("UserDir: %s\n", getpwnam(argv[1])->pw_dir);
  exit(0);
}

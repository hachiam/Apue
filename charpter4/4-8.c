#include "apue.h"

int main() {
  if (chdir("/tmp") < 0) printf("chdir failed");

  printf("chdir succeed\n");
  exit(0);
}

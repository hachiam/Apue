#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  printf(getlogin());
  return 0;
}


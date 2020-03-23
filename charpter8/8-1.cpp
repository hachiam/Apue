// fork exmple
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
using namespace std;

int bob = 6;
char buf[] = "a write to stdout";
void err_quit(string msg) {
  cout << msg << endl;
  exit(0);
}

int main(int argc, char *argv[])
{
  int var = 88;
  pid_t pid;
  if (write(STDOUT_FILENO, buf, sizeof(buf-1)) != sizeof(buf - 1))
    err_quit("write to stdout error");
  printf("before fork\n");

  if ((pid = fork()) < 0)
    err_quit("fork failed");
  else if (pid == 0) { //child
    bob++;
    var++;
  } else {
    sleep(2);
  }
  printf("the bob is %d, and the var is %d\n",bob, var );
  return 0;
}


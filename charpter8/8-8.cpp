#include <iostream>
#include "apue.h"
using namespace std;
int main(int argc, char *argv[])
{
  pid_t pid;

  if ((pid = fork()) < 0)
    err_quit("fork error");
  else if (pid == 0) { //child
    execlp("ls", "-la", " ");
  }
  else
    cout << "parent " << "\n";
  
  return 0;
}


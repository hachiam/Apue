#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string>
using namespace std;
void err_quit(string msg) {
  std::cout << msg << "\n";
  exit(0);
}

int main(int argc, char *argv[])
{
  pid_t pid;
  if ((pid = fork()) < 0)
    err_quit("fork failed");
  else if (pid == 0) { //the first child
    if ((pid = fork()) < 0)
      err_quit("fork failed");
    else if (pid > 0)  //the first child and also the father of the second child
      exit(0); 

    sleep(2);
    std::cout << "second child , parent pid = " << getpid();
    exit(0);
  }

  if (waitpid(pid, NULL, 0) != pid)
    err_quit("waitpid error");
  return 0;
}


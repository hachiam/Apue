#include <iostream>
#include <unistd.h>
#include <string>
#include <stdlib.h>
using namespace std;
void err_quit(string msg) {
  cout << msg << "\n";
}
int bob = 9;
// use vfork 代替 fork，直接占用父亲进程的资源，父亲进程在他退出前处于休眠。
// 子进程在父亲进程的地址空间执行，所以改变了父亲进程的值。
int main(int argc, char *argv[])
{
  int var = 88;
  pid_t pid;

  if ((pid = vfork()) < 0)
    err_quit("vfork failed") ;
  else if (pid == 0) { //child
    var++;
    bob++;
    exit(0);
  }
  //father continue
  cout << "pid : " << getpid() << endl;
  cout << "bob: " << bob << " var: "<< var << "\n";
  exit(0);
}


#include "apue.h"

int sig_int_flag;

int main() {
  int sig_int();
  signal(SIGINT, sig_int);
  while (sig_int_flag == 0)
    pause();

}

int sig_int() {
  signal(SIGINT, sig_int);
  sig_int_flag = 1;
}

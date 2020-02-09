#include <setjmp.h>

#include "apue.h"

//进行命令行处理的典型程序骨架
#define TOK_ADD 5
jmp_buf jmpbuffer;

void do_line(char *);
void cmd_add();
int get_token();

int main() {
  char line[MAXLINE];

  if (setjmp(jmpbuffer) != 0) printf("error");

  while (fgets(line, MAXLINE, stdin) != NULL) do_line(line);
  exit(0);
}

char *tok_ptr;  // global pointer for get_token()

void do_line(char *ptr) {
  int cmd;

  tok_ptr = ptr;
  while ((cmd = get_token()) > 0) {
    switch (cmd) {
      case TOK_ADD:
        cmd_add();
        break;
    }
  }
}

void cmd_add() {
  int token;

  token = get_token();
  if (token < 0) {
    longjmp(jmpbuffer, 1);
  }
}

int get_token() {}

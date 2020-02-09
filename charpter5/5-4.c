#include "apue.h"

int main() {
  char name[L_tmpnam], line[MAXLINE];
  FILE *fp;

  printf("%s\n", tmpnam(NULL));  // first temp name;
  tmpnam(name);                  // second tmpname
  printf("%s\n", name);

  // create tempfile
  if ((fp = tmpfile()) == NULL) err_sys("tmpfile error");
  fputs("one line of the output \n", fp);  // write to tempfile
  rewind(fp);                              // then read it back

  if (fgets(line, sizeof(line), fp) == NULL) err_sys("fgets error");

  fputs(line, stdout);  // print the line that we wrote
  exit(0);
}

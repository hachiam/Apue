#include "apue.h"
#include <fcntl.h>

//access 函数的用法

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("usage: a.out <pathname>");
		exit(1);
	}
	if (access(argv[1], R_OK) < 0)
		printf("access error for %s\n",argv[1] );
	else
		printf("read access OK!");

	if (open(argv[1], O_RDONLY) < 0)
		printf("open file error for %s", argv[1]);
	else
		printf("open for reading\n");

	exit(0);
}

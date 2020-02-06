#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE 4096
char buf1[] = "abcdefghij";

int main() {
	int fd;

	if ((fd = creat("file.test", FILE_MODE)) < 0)
		printf("create file error");
	if (write(fd, buf1, 10) != 10)
		//offset 10
		printf("write error");

	if ((fd = open("file.test", O_RDWR)) == -1)
		printf("open file error");

	if (lseek(fd, 5, SEEK_SET) == -1)
		printf("lseek failed");
	//offset 5
	if (write(fd, buf1, 8) != 8)
		printf("write buf error");

	exit(0);
}

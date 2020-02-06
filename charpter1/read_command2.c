#include "apue.h"
#include <sys/wait.h>

static void sig_int(int);
int main() {
	char buf[MAXLINE];
	pid_t pid;
	int status;

	if (signal(SIGINT, sig_int) == SIG_ERR)
		printf("signal error");
	printf("%% ");
	while(fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1 == '\n' ])
			buf[strlen(buf) - 1] = 0; //replace newline with NULL

		if ((pid = fork()) < 0) {
			printf("fork error");
		} else if (pid == 0) {
			execlp(buf, buf, (char *)0);
			printf("could't execute: %s", buf);
			exit(127);
		}

		//parents
		if ((pid = waitpid(pid, &status, 0)) < 0)
			printf("waitpid error");
		printf("%% ");
	}
}

void sig_int(int signo) {
	printf("interrput\n%% ");
}

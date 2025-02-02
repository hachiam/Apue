#include "apue.h"
#include<errno.h>
#include <limits.h>

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

#define SUSV3 200112L
static long posix_version = 0;

#define PATH_MAX_GUESS 1024

char *
path_alloc(int *sizep) {
	char *ptr;
	int size;

	if (posix_version == 0) 
		posix_version = sysconf(_SC_VERSION);

	if (pathmax == 0) {
		errno = 0;
	if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
		if (errno == 0)
			pathmax = PATH_MAX_GUESS;
		else 
			printf("pathconf err for _PC_PATH_MAX");
	} else {
		pathmax++;
	}

    }
	if (posix_version < SUSV3)
		size = pathmax + 1;
	else
		size = pathmax;
	if ((ptr = malloc(size)) == NULL)
		printf("malloc error for pathname");

	if (sizep != NULL)
		*sizep = size;
	return(ptr);

}



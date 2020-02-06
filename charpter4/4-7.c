#include <dirent.h>
#include <fcntl.h>
#include <limits.h>

#include "apue.h"

/*function type that is called for each filename*/
typedef int Myfunc(const char *, const struct stat, int);

static Myfunc myfunc;
static int myftw(char *, Myfunc *);
static int dopath(Myfunc *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char *argv[]) {
  int ret;

  if (argc != 2) {
    printf("usage ftw <starting_filepath>");
    exit(0);
  }

  ret = myftw(argv[1], myfunc);  // does it all
  ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock + ntot;
  if (ntot == 0) ntot = 1;
  printf("reguler files = %71d, %5.2f %%", nreg, nreg * 100.0 / ntot);
  printf("directionaries files = %71d, %5.2f %%", ndir, ndir * 100.0 / ntot);
  printf("block special files = %71d, %5.2f %%", nblk, nblk * 100.0 / ntot);
  printf("char special files = %71d, %5.2f %%", nchr, nchr * 100.0 / ntot);
  printf("fifo files = %71d, %5.2f %%", nfifo, nfifo * 100.0 / ntot);
  printf("sympol link files = %71d, %5.2f %%", nslink, nslink * 100.0 / ntot);
  printf("socket files = %71d, %5.2f %%", nsock, nsock * 100.0 / ntot);

  exit(ret);
}

#define FTW_F 1         // file other than directionary
#define FTW_D 2         // directionary
#define FTW_DNR 3       // directionaries that can't be read
#define FTW_NS 4        // file that we can't stat
static char *fullpath;  // contains fullpath filename for each file

static int myftw(char *pathname, Myfunc *func) {
  int len;
  fullpath = path_alloc(&len);  // malloc 's for path_MAX+1 bytes
  strncpy(fullpath, pathname, len);
  fullpath[len - 1] = 0;  // buffer overrrun

  return dopath(func);
}

static int dopath(Myfunc *func) {
  struct stat statbuf;
  struct dirent *dirp;
  DIR *dp;
  int ret;
  char *ptr;

  if (lstat(fullpath, &statbuf) < 0) return (func(fullpath, &statbuf, FT_NS));
  if (S_ISDIR(statbuf.st_mode) == 0)
    return (func(fullpath, &statbuf, FTW_F));  // not a directionary

  // It's a directionary . first call func() for this directionary
  if ((ret = func(fullpath, &statbuf, FTW_D)) != 0) return (ret);
  ptr = fullpath + strlen(fullpath);  // point to end of fullpath
  *ptr++ = '/';
  *ptr = 0;

  if ((dp = opendir(fullpath)) == NULL)  // can't read directionary
    return (func(fullpath, &statbuf, FTW_DNR));

  while ((dirp = readdir(dp)) != NULL) {
    if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
      continue;

    strncpy(ptr, dirp->d_name);  // append name after slash

    if ((ret = dopath(func)) != 0) break;
  }
  ptr[-1] = 0;

  if (closedir(dp) < 0) printf("cant'close directionary %s", fullpath);
  return (ret);
}

static int myfunc(const char *pathname, const struct stat *statptr, int type) {
  switch (type) {
    case FTW_F:
      switch (statptr->st_mode & S_IFMT) {
        case S_IFREG:
          nreg++;
          break;
        case S_IFBLK:
          nblk++;
          break;
        case S_IFCHR:
          nchr++;
          break;
        case S_IFIFO:
          nfifo++;
          break;
        case S_IFLNK:
          nslink++;
          break;
        case S_IFSOCK:
          nsock++;
          break;
        case S_IFDIR:
          printf("for S_IFDIR for %s", pathname);
      }
      break;
    case FTW_D:
      ndir++;
      break;
    case FTW_DNR:
      printf("can't read directory %s", pathname);
    case FTW_NS:
      printf("stat err for %s", pathname);
    default:
      printf("utknow type %d for pathname %s", type, pathname);
  }
  return (0);
}

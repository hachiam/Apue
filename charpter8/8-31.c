#include "apue.h"
#include "pr_exit.h"
#include <sys/times.h>

static void pr_times(clock_t, struct tms *, struct tms *);
static void do_cmd(char *);

int main(int argc, char *argv[])
{
  int i;
  for (i = 1; i < argc; ++i)
    do_cmd(argv[i]);
  exit(0);
}

static void
do_cmd(char *cmd) {
  struct tms tmstart, tmsend;
  clock_t start, end;
  int status;

  printf("\ncommand: %s\n", cmd);

  if ((start = times(&tmstart)) == -1)
    err_sys("times error");

  if ((status = system(cmd)) < 0)
    err_sys("system() error");

  if ((end = times(&tmsend)) == -1)
    err_sys("times error");

  pr_times(end-start, &tmstart, &tmsend);
  pr_exit(status);
}

static void
pr_times(clock_t real, struct tms *tmstart, struct tms *tmsend)
{
  static long clktck = 0;

  if (clktck == 0)
    if ((clktck = sysconf(_SC_CLK_TCK)) < 0)
      err_sys("sysconf error");

  printf("real : %7.2f\n", real / (double) clktck);
  printf("user : %7.2f\n",
	 (tmsend->tms_utime - tmstart->tms_utime) / (double) clktck);
  printf("sys : %7.2f\n",
	 (tmsend->tms_stime - tmstart->tms_stime) / (double) clktck);
  printf(" child user: %7.2f\n",
	 (tmsend->tms_cutime - tmstart->tms_cutime) / (double) clktck);
  printf("sys : %7.2f\n",
	 (tmsend->tms_cstime - tmstart->tms_cstime) / (double) clktck);

}


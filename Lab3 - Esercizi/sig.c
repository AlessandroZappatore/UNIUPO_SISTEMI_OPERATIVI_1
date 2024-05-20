#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

void f_intr(int sig)
{
  printf("ricevuto il segnale numero : %d\n",sig);
}
int main(int argc, char *argv[])
{
  int m,n;
  struct sigaction sa;

  fork();
  sa.sa_handler = f_intr;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGINT,&sa,NULL);
  for (m=0;m<100;m++)
  {
    for (n=0;n<200000000;n++);
    printf("working %d, pid %d\n",m, getpid());
  }
  return 0;
}

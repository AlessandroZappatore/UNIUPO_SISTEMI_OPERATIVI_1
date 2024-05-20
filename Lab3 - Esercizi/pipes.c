#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
  int pipefd[2];

  pipe (pipefd);

  if (fork() == (pid_t)0) {
	/* primo figlio esegue "wc -l " (conta righe) prendendo 
           l'input da pipefd[0] */
	dup2(pipefd[0],0); 
	close(pipefd[0]);
	close(pipefd[1]);
	execlp("tail","tail","-10",NULL);
	perror("exec wc fallita");
  }
  else if (fork() == (pid_t)0) {
	/* secondo figlio esegue "ls -l" mandando l'output 
	   su pipefd[1] */
	dup2(pipefd[1],1);
	close(pipefd[0]);
	close(pipefd[1]);
	execlp("head","head","-20","pipes.c",NULL);
	perror("exec ls fallita");
       }
       else
       { /* processo padre chiude entrambi gli estremi della pipe 
	    e attende i figli */
         close(pipefd[0]);
	 close(pipefd[1]);
	 wait(NULL);
	 wait(NULL);
       }	
  return 0;
}

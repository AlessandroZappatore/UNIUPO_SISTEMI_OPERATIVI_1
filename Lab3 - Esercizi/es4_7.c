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
	execlp("more","more",NULL);
	perror("exec more fallita");
  }
  else if (fork() == (pid_t)0) {
	/* secondo figlio esegue "ls -l" mandando l'output 
	   su pipefd[1] */
	dup2(pipefd[1],1);
	close(pipefd[0]);
	close(pipefd[1]);
	execlp("cat","cat",argv[1],NULL);
	perror("exec cat fallita");
       }
       else if(fork() == (pid_t)0)
       { 
        dup2(pipefd[1],1);
        close(pipefd[0]);
        close(pipefd[1]);
        execlp("cat","cat",argv[2],NULL);
        perror("exec cat fallita");
       }
       else
       {
        close(pipefd[0]);
        close(pipefd[1]);
        wait(NULL);
        wait(NULL);
        wait(NULL);
       }
  return 0;
}

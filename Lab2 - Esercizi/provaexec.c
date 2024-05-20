#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{ 
  pid_t n,m;
  int s;
  char* arg[]={"Hello", NULL};
  
  
  if((n=fork())== (pid_t)-1)
	{perror("fork fallita");
	 exit(1);
	}

  else if (n==(pid_t)0)
		{/* processo figlio */
 
		execv("hello",arg);
		perror("exec fallita");
		}
       else
		{/* processo padre */
		m=wait(&s);
 		if (m==-1) perror("wait"); 
		}
   return 0;
}

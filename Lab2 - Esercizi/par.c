#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

	int i,j;
	pid_t n;
	
	n=fork();
	if (n==(pid_t)-1)
	{perror("fork fallita");
		 exit(1);
	};
	if (n==(pid_t)0) {
	  for (j=0;j<50;j++) {
		for (i=0; i< 100000000; i++);
		printf("     Figlio %d di %d giro %d, n=%d \n",getpid(),getppid(),j, n );
		fflush(stdout);
	  }
	}
	else {
	  for (j=0;j<20;j++) {
		for (i=atoi(argv[2]); i< 100000000; i++);
		printf("Padre %d di n=%d giro %d\n",getpid(),n,j);
		fflush(stdout);
	  }
	}
	return 0;
}

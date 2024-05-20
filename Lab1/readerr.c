#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  int f,i,n,ne;
  char buf[20];

  f=open("fileprova",O_RDONLY);
  if (f==-1) { 
    perror("Errore apertura file!");
	return 1; 	/* qualcosa non e' andato bene */
  }
  else
	{
	printf("Numero bytes da leggere (max 20): ");
	scanf("%d",&n);
	if (n>20) n=20;
	ne=read(f,buf,n);
	printf("letti %d caratteri: ",ne);
	for (i=0;i<ne;i++) putchar(buf[i]);
	printf("\n");
	return 0; 	
	}
}


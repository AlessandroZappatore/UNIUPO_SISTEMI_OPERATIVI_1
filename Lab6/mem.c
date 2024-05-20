/* 
   PASSARE -lrt a gcc PER IL COLLEGAMENTO

   stampando il valore di alcuni puntatori, 
   illustra come vengono assegnati gli indirizzi (virtuali) 
   dal compilatore, da malloc e da mmap (dopo shm_open)

*/

#include <malloc.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

int ext1,ext2;

void f(int n)
{
  int a;

  static int s;
  
  /* stampa l'indirizzo del parametro, della variabile "automatica"
     e della variabile "statica" */

  printf("%p %p %p\n",&n, &a, &s);
  if (n>0) f(n-1);
}

int main()

{

int b,c,n;

int shm_fd1,*a1;
int shm_fd2;
char *a2;

/* stampa l'indirizzo delle variabili globali e di quelle interne al main */

printf("var esterne: %p %p\n",&ext1,&ext2);

printf("interne al main: %p %p\n",&b, &c);

printf("dati della funzione: parametro, var. automatica, var. statica \n");

/* la funzione e' ricorsiva, f(5) da' luogo a 5 chiamate ricorsive:
   per ogni chiamata, sulla stack c'e' una copia diversa del parametro 
   e delle variabili locali - ma non di quelle statiche */

f(5);

/* stampa i valori restituiti da chiamate successive di malloc */

printf("malloc : %p\n",malloc(1024));
printf("malloc : %p\n",malloc(1024));
printf("malloc : %p\n",malloc(1024));
printf("malloc : %p\n",malloc(1024));

/* alloca memoria condivisa per un array di 100 interi */

shm_fd1 = shm_open("/myshm1", O_CREAT|O_RDWR,0600);
if (shm_fd1 == -1) perror("Creazione memoria condivisa");

ftruncate(shm_fd1,100*sizeof(int));

/* alloca memoria condivisa per un array di 100 caratteri */

shm_fd2 = shm_open("/myshm2", O_CREAT|O_RDWR,0600);
if (shm_fd2 == -1) perror("Creazione memoria condivisa");

ftruncate(shm_fd2,100*sizeof(char));

n= fork();
if (n == -1) perror("Fork");

if (n == 0)
   {  /* processo figlio */
	a1 = mmap(0,100*sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED, shm_fd1,0);
	printf("mmap processo figlio array interi : %p\n",a1);
	a2 = mmap(0,100*sizeof(char),PROT_READ|PROT_WRITE,MAP_SHARED, shm_fd2,0);
	printf("mmap processo figlio array caratteri: %p\n",a2);
	a1[0]=10;	/* scrive in memoria condivisa */
	a2[0]='q';
   }
else
   {  /* processo padre */
	a2 = mmap(0,100*sizeof(char),PROT_READ|PROT_WRITE,MAP_SHARED, shm_fd2,0);
	printf("mmap processo padre array caratteri: %p\n",a2);
	a1 = mmap(0,100*sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED, shm_fd1,0);
	printf("mmap processo padre array interi : %p\n",a1);
	wait(NULL);
	printf("Dall'array condiviso di interi: %d e da quello di caratteri: %c \n",a1[0],a2[0]);
   }

return 0;

}

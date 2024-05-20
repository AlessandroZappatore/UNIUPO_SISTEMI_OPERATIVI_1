
/********  N produttori, 1 consumatore con semafori e thread ********/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define N 5    		/* dim. buffer */
#define NPROD 5    	/* numero produttori */
#define NGIRI 20 	/* quanti caratteri prodotti da ogni produttore */
int inseriti=0, consumati=0;
struct buffer{
        char pool[N];
        int in,out,count;
        } buf;

sem_t mutex,empty,full;


void printstatus()	/* stampa contenuto del buffer */
{
  int i;
 
  printf("Contenuto del buffer:");
  for (i=0;i<buf.count;i++)
      putchar(buf.pool[(buf.out+i)%N]);
}

void put(char i)
{
 
  buf.pool[buf.in]=i;
  buf.in = (buf.in+1)%N;
  buf.count++;
 
  printstatus();
  printf(" dopo put del carattere %c\n",i);
  fflush(stdout); /* cosi' va bene anche se si ridirige l'output su disco */
}

void get(char *ip)
{

  *ip=buf.pool[buf.out];
  buf.out = (buf.out+1)%N;
  buf.count--;
  
  printstatus();
  printf(" dopo get del carattere %c\n",*ip);
  fflush(stdout); /* cosi' va bene anche se si ridirige l'output su disco */
}
 

void *producer(void *p)	/* produce NGIRI volte il carattere *p */
{
  int i;

  for (i=0;i<NGIRI;i++)
        {
 
	int j;
        for (j=0;j<1000000;j++); /* per rallentare */

	sem_wait(&empty);
        sem_wait(&mutex);
        put(*(char *)p);
        inseriti++;
        sem_post(&mutex);
	sem_post(&full);
        }
  return NULL;
}

void *consumer(void *filename)	/* copia da buffer a filename */
{
  char c;
  FILE *res;
 
  res=fopen((char *) filename,"w");

  do /* esce quando trova il carattere \0 nel buffer */
  {
  	int i;
 
  	for (i=0;i<1000000;i++); /* per rallentare */
 
  	sem_wait(&full);
  	sem_wait(&mutex);
  	get(&c);
    consumati++;
  	sem_post(&mutex);
  	sem_post(&empty);
	
  	putc(c,res);
  }
  while (c!=0);
  return NULL;
}

 
int main(int argc, char *argv[])
{

int i;
char c[NPROD];
pthread_t t[NPROD+1];

sem_init(&mutex,0,1);

sem_init(&empty,0,N);

sem_init(&full,0,0);


if (argc != 2) 
{
	fprintf(stderr,"un nome di file come argomento\n");
	exit(1);
}

buf.in = buf.out = buf.count = 0;
 
/* genera produttori e consumatore */

fflush(stdout);


for(i=0;i<NPROD;i++)
	{
	  c[i]='0'+i;
	  pthread_create(&t[i], NULL, producer, &c[i]);
	}

pthread_create(&t[i], NULL, consumer, argv[1]);

for(i=0;i<NPROD;i++)
	pthread_join(t[i], NULL);

/* produce carattere 0 per far terminare il consumatore */
sem_wait(&empty);
sem_wait(&mutex);
put(0);
sem_post(&mutex);
sem_post(&full);

pthread_join(t[i],NULL);

printf("Numero di items inseriti %d\n Numero di items consumati %d\n", inseriti, consumati);
}


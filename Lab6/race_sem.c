#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <pthread.h>


int k;
int *m;
int shm_fd1, shm_fd2;
sem_t *mutex;


int main(int argc, char *argv[])
{ 
  pid_t n;
  int j;
  
  if (argc!=2) {
    fprintf(stderr,"Chiamare con un argomento numerico\n");
    exit(1);
  }
 
  k = atoi(argv[1]);  
  
  
  shm_fd1 = shm_open("/myshm1", O_CREAT|O_RDWR,0600);
  if (shm_fd1 == -1) perror("Creazione memoria condivisa: shm_open stato");
  ftruncate(shm_fd1,sizeof(int));
  m = mmap(0, sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED, shm_fd1,0);
  if (m == MAP_FAILED) perror("Creazione memoria condivisa: mmap stato");
  *m = 10;
  
  shm_fd2 = shm_open("/myshm2", O_CREAT|O_RDWR,0600);
  if (shm_fd2 == -1) perror("Creazione memoria condivisa: shm_open semaforo");

  ftruncate(shm_fd2,sizeof(sem_t));
  
  mutex = (sem_t *) mmap(0, sizeof(sem_t),PROT_READ|PROT_WRITE,MAP_SHARED, shm_fd2,0);
  if (mutex == MAP_FAILED) perror("Creazione memoria condivisa: mmap semaforo");

    
  
  sem_init(mutex,1,1);
  
  if((n=fork())== (pid_t)-1){
    perror("fork fallita");
    exit(1);    
  }
  else if (n==(pid_t)0)
        {/* processo figlio */
	  printf("Il pid del figlio e' %d\n", getpid()); 
	  for (j=0;j<k;j++){  
	    sem_wait(mutex); 
	    (*m)++;	
	    sem_post(mutex);
	  }
	  exit(0);
	}
        else
	{/* processo padre */
	  printf("Il pid del padre e' %d\n", getpid());
	  for (j=0;j<k;j++){
        sem_wait(mutex); 
	    (*m)--;	
	    sem_post(mutex);	
	  }
	  wait(NULL);
	  printf(" m = %d \n",*m);
	}
}

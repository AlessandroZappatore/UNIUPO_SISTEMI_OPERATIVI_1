#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int k;
int n=10;
pthread_mutex_t m;

void *tbody(void *arg)
{

        int j;
        pthread_mutex_lock(&m);
        for (j=0;j<k;j++)  n++;
        pthread_mutex_unlock(&m);
        pthread_exit(NULL); 
}

int main(int argc, char *argv[])
{
        int j;
        pthread_t t;
        pthread_mutex_init(&m, NULL);
	if (argc!=2) {
		fprintf(stderr,"Chiamare con un argomento numerico\n");
		exit(1);
	}
 
        k = atoi(argv[1]);

        pthread_create(&t, NULL, tbody, NULL);
        pthread_mutex_lock(&m);
        for (j=0;j<k;j++)  n--;
        pthread_mutex_unlock(&m);
        pthread_join(t, NULL);

        printf(" n = %d \n",n);

}



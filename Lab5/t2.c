#include <pthread.h>
#include <stdio.h>

int flag=0;

void *tbody(void *arg)
{

		printf("T2 flag = %d  \n",flag);

        pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
        pthread_t t;
        void *status;

        pthread_create(&t, NULL, tbody, NULL);

		printf("un carattere, prego\n");

        getchar(); /* il thread si sospende */

		flag = 1;

		printf("T1 flag = %d  \n",flag);

        pthread_join(t, &status);
}


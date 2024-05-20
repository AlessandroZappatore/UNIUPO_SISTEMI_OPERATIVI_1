#include <pthread.h>
#include <stdio.h>

void *tbody(void *arg)
{

        int i;

        for (i=0; i< 500000000; i++);

        printf("Il nuovo thread ha finito\n");
}


int main(int argc, char *argv[])
{
        pthread_t t;
        void *status;

        pthread_create(&t, NULL, tbody, NULL);

		printf("un carattere, prego\n");

        getchar(); /* il thread si sospende */

        pthread_join(t, &status);
}


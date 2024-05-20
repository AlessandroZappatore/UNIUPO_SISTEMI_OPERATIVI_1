#include <pthread.h>
#include <stdio.h>
int a;

void *tbody(void *arg)
{

	int j;

	printf("   Thread due\n");

	*(int *)arg = 10; 
	a=10;
	for (j=0;j<1000000000;j++); /* per vedere che chi fa join aspetta */

	pthread_exit(NULL); /* oppure return(NULL); */
}

int main(int argc, char *argv[])
{
	int i=2;
	pthread_t t;
	void *result;
	a=30;
	pthread_create(&t, NULL, tbody, (void *) &i);

	/* e' equivalente dichiarare pthread_attr_t tattr; e chiamare
	pthread_attr_init(&attr);
	pthread_create(&t, &tattr, tbody, &i); 
	se invece si vogliono usare attributi diversi da
	quelli di default, li si modificano tra attr_init e create */

	printf("Thread uno \n");

	pthread_join(t, &result);

	printf("a = %d\n", a);
	if (result == NULL) 
		printf("Il thread creato ha assegnato %d ad i\n",i);

}


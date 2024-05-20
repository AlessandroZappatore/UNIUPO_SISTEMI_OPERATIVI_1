#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{  
   int n=creat("pippo", S_IRUSR | S_IWUSR);  /* ahi, non controlliamo eventuali errori... */
   close(1); /* chiude lo standard output */
   dup(n);   /* ora il descrittore 1 e' associato a pippo */
   close(n);
   printf("Hello \n");  /* oppure write(1,"Hello \n",7); */
   return 0;
}

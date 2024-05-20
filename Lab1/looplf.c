#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int n=1000,i;

    if (argc==2) n=atoi(argv[1]);

    for(i=0;i<n;i++)
        putchar('q');
}

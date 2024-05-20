#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int n=1000,i;

    if (argc==2) n=atoi(argv[1]);

    for(i=0;i<n;i++)
        write(1,"Q",1);

    return 0;
}
    


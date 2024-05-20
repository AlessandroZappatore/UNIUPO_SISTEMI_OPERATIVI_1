#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc==2)
    {
        FILE* fp=fopen(argv[1], "w");
        if(fp!=NULL)
        {
            pid_t p1=fork();
            if(p1==(pid_t)-1)
            {
                perror("Errore fork 1\n");
                return -1;
            }
            if(p1==(pid_t)0)
            {
                pid_t p2=fork();
                if(p2==(pid_t)-1)
                {
                    perror("Errore fork 2");
                    return -1;
                }
                if(p2==(pid_t)0)
                {
                    fprintf(fp, "Sono il processo P3 con pid <%d>\n", getpid());
                }
                else
                {
                    wait(NULL);
                    fprintf(fp, "Sono il processo P2 con pid <%d>\n", getpid());
                }
            }
            else
            {
                wait(NULL);
                fprintf(fp, "Sono il processo P1 con pid <%d>\n", getpid());
            }
            fclose(fp);
        }
        else
        {
            perror("Errore file\n");
            return -1;
        }
    }
    else 
    {
        perror("Numero di argomenti errato\n");
        return -1;
    }
}
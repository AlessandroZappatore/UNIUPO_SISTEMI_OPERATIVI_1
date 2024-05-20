#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){
    int fp=open(argv[1], O_RDWR|O_CREAT);
    if(fp==-1){
        perror("Errore durante l'apertura del file");
        return 1;
    }
    close(1);
    dup2(fp,1);
    close(fp);
    int w=write(1, "PROVA133\n", 9);
    if(w==-1){
        perror("Errore durante la scrittura sul file\n");
        return 1;
    }
    return 0;
}
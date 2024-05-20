/*Scrivere un programma che usando le funzioni di I/O unbuffered:
- prende in input il nome di un file passato come argomento
- apre o crea il file, in caso di creazione deve dare permessi di lettura e
scrittura al proprietario e al gruppo
- Il file deve essere aperto in modalità append
- Scrive una stringa a piacere nel file
- Chiude il file*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    int fp=open(argv[1], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP |S_IWGRP);
    write(fp, "PROVA!\n", 7);
    close(fp);  
    return 0;
}
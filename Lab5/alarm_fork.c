#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef struct alarm{
  int seconds;
  char message[64];
  alarm_t;
}
void* esegui(void *arg)
{
  alarm=
  sleep(alarm.seconds);
  printf("(%d) %s\n", alarm.seconds, alarm.message);
}

int main(int argc, char *argv[]){
  char line[128];
  int seconds;
  pid_t pid;
  char message[64];
  pthread_t t;
  
  while(1){
    printf("Allarme >");
    
    //Legge da linea di comando e inserisce in line
    if(fgets(line, sizeof(line), stdin)==NULL) exit(0);
    if(strlen(line)<=1) continue;
    
    //Parsing deve essere un entero e un mesaggio .... [^\n] esclude lo \n
    if(sscanf(line, "%d %64[^\n]", &seconds, message)<2) {
      fprintf(stderr, "Comando sconosciuto\n");
    } 
    else {
      pthread_create(&t, NULL, esegui(seconds, message), NULL);    
    }              
  }
}
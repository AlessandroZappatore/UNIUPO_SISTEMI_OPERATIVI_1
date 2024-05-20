#include "smallsh.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char *prompt = "Scrivere un comando>";

void procline(void) 	/* tratta una riga di input */
{

  char *arg[MAXARG+1];	/* array di puntatori per runcommand */
  int toktype;  	/* tipo del simbolo nel comando */
  int narg;		/* numero di argomenti considerati finora */
	
  narg=0;

  do {

    /* mette un simbolo in arg[narg] 
       ed esegue un'azione a seconda del tipo di simbolo */
	
    switch (toktype = gettok(&arg[narg])) {
	
      case ARG:   

        /* se argomento: passa al prossimo simbolo */
		
        if (narg < MAXARG) narg++;
	break;
       

      case EOL:
      case SEMICOLON:
      
         /* se fine riga o ';' esegue il comando ora contenuto in arg,
	 mettendo NULL per indicare la fine degli argomenti: 
         serve a execvp */

        if (narg != 0) {
          arg[narg] = NULL;
          runcommand(arg,0);
        }
      
	/* se non fine riga (descrizione comando finisce con ';')
           bisogna ricominciare a riempire arg dall'indice 0 */

        if (toktype != EOL)  narg = 0; 
  
        break;
      case AMPERSAND:
        if(narg!=0)
        {
          arg[narg]=NULL;
          runcommand(arg, 1);
        }
        if (toktype != EOL)  narg = 0; 
      break;
     }
  }

  while (toktype != EOL);  /* fine riga, procline finita */

}

void runcommand(char **cline, int background)	/* esegue un comando */
{
  pid_t pid;
  int exitstat,ret;

  pid = fork();
  if (pid == (pid_t) -1) {
     perror("smallsh: fork fallita");
     return;
  }

  if (pid == (pid_t) 0) { 	/* processo figlio */

    /* esegue il comando il cui nome e' il primo elemento di cline,
       passando cline come vettore di argomenti */

    execvp(*cline,cline);
    perror(*cline);
    exit(1);
  }

  /* non serve "else"... ma bisogna aver capito perche' :-)  */
 
  /* qui aspetta sempre e comunque - i comandi in background 
     richiederebbero un trattamento diverso */

  if (!background) {
    ret = waitpid(pid, &exitstat, 0);

    if (ret == -1) perror("wait");
  } else {
    printf("Comando in background con PID: %d\n", pid);
  }

  while ((pid = waitpid(-1, &exitstat, WNOHANG)) > 0) {
        printf("Background pid %d is done\n", pid);
	}
}

int main()
{
  while(userin(prompt) != EOF)
    procline();
  return 0;
}
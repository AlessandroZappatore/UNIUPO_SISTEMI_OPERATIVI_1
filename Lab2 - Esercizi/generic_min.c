#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 5 /* numero elementi di lineptr */

char *lineptr[] = {"esempio", "cosi", "puntitore", "zz", "funzione"};  /* elenco di parole su cui calcolare il minimo lessicografico */
/* int  lineptr[] = {4, 3, 2, 1, 5}; */


void *generic_min(void **v, int n, int (*comp)(void *, void *)){
  
  int min_idx, j;
  
  if(v != NULL){  /* Se l'array non è vuoto...*/
    min_idx = 0;  /* il minimo di un array di un solo elemento è l'elemento stesso, di indice 0*/
    for (j = 1; j < n; j++)               /* esamino i restanti elementi */
      if (comp(v[j], v[min_idx]) < 0)     /* se l'elemento corrente è minore dell'attuale minimo... */
        min_idx = j;                      /* diventa il nuovo minimo */
    return v[min_idx];
  } 
  else
    return NULL;
}


int main(int argc, char *argv[])
{
  void *r; 
  int a, b;
  void *p;
  
  
  /* Semplice esempio di uso di puntatori generici */
  a = LEN;
  p = (void *) &a;        /* p punta alla variabile intera a */
  b = *( (int *) p);    /* eseguo cast prima di deferenziare  */
  printf("Lunghezza array: %d\n", b);
  
  /* Uso di puntatori generici e puntatore a funzione*/
  r = generic_min((void **) lineptr, LEN, (int (*)(void *, void *)) strcmp);
  
  if(r!=NULL)
    printf("Il minimo è: %s\n", (char *) r);
  
  return 0;
}

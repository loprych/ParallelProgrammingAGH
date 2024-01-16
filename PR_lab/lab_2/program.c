#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>

#include "pomiar_czasu.h"

int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku( void* argument )
{
  int local_value = *(int *)argument;
    for(int i = 0; i < 1e+5; i++){
        zmienna_globalna++;
        local_value++;
    }
   // *(int *) argument = local_value;
    printf("Wewnatrz funkcji:\n");
    printf("Zmienna globalna: %d\n",zmienna_globalna);
    printf("Zmienna lokalna: %d\n",local_value);
  // /* int wynik; */
  /* wynik=execv("./program",NULL); */
  /* if(wynik==-1) */
  /*   printf("Proces potomny nie wykonal programu\n"); */

  return 0;
}

int main()
{

  void *stos, *stos1; 
  pid_t pid, pid1;
  int i;
  int local_value = 0;

  stos = malloc( ROZMIAR_STOSU );
  stos1 = malloc( ROZMIAR_STOSU );
  if (stos == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }

  inicjuj_czas();

    pid = clone( &funkcja_watku, (void *) stos+ROZMIAR_STOSU,CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &local_value );
    pid1 = clone( &funkcja_watku, (void *) stos1+ROZMIAR_STOSU, CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &local_value );

    waitpid(pid, NULL, __WCLONE);
    waitpid(pid1, NULL, __WCLONE);

  //drukuj_czas();
  printf("Wewnatrz maina:\n");
  printf("Zmienna globalna: %d\n",zmienna_globalna);
  printf("Zmienna lokalna: %d\n",local_value);
  free( stos );
  free( stos1 );
}

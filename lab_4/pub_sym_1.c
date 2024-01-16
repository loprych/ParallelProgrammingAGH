#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define ILE_MUSZE_WYPIC 3

int liczba_kufli = 0; //zmienna globalna
pthread_mutex_t mutex; //inicjalizacja mutexa
int l_kranow;
void * watek_klient (void * arg);

int main( void ){


  pthread_t *tab_klient;
  int *tab_klient_id;

  int l_kl, l_kf, l_kr, i;


  printf("\nLiczba klientow: "); scanf("%d", &l_kl);

  printf("\nLiczba kufli: "); scanf("%d", &l_kf);
	
  liczba_kufli = l_kf;
 
  //printf("\nLiczba kranow: "); scanf("%d", &l_kr);
  l_kr = 1; // wystarczająco dużo, żeby nie było rywalizacji 
  l_kranow = l_kr;
  tab_klient = (pthread_t *) malloc(l_kl*sizeof(pthread_t)); // alokacja pamieci zm pthread pomnozona przez liczbe klientów
  tab_klient_id = (int *) malloc(l_kl*sizeof(int)); // tworzenie tab intów
  for(i=0;i<l_kl;i++) tab_klient_id[i]=i; 
  printf("\nOtwieramy pub (simple)!\n");
  printf("\nLiczba wolnych kufli %d\n", l_kf); 

  for(i=0;i<l_kl;i++){
    pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]); 
  }
  for(i=0;i<l_kl;i++){
    pthread_join( tab_klient[i], NULL);
  }
    printf("\nZamykamy pub!\n");
  if (liczba_kufli == l_kf ) {
    printf("Ilość kufli się zgadza\n");
  }
  else {
    printf("Liczba kufli się nie zgadza\n");
  }
    printf("Liczba kufli : %d\n", liczba_kufli);
}

void * watek_klient (void * arg_wsk){

  int moj_id = * ((int *)arg_wsk);

  int i, j, kufel, result;
  int ile_musze_wypic = ILE_MUSZE_WYPIC;

  long int wykonana_praca = 0;

  printf("\nKlient %d, wchodzę do pubu", moj_id); 
    
      
  for(i=0; i<ile_musze_wypic; i++){
    
    pthread_mutex_lock (&mutex);
    printf("\nKlient %d, wybieram kufel nr:%d", moj_id, liczba_kufli); 
    liczba_kufli--;
    pthread_mutex_unlock (&mutex);
    //j=0;
    pthread_mutex_lock (&mutex);
    printf("\nKlient %d, nalewam z kranu %d", moj_id, l_kranow); 
    usleep(1);
    pthread_mutex_unlock (&mutex);
    
    printf("\nKlient %d, pije", moj_id); 
    nanosleep((struct timespec[]){{0, 50000000L}}, NULL);
    pthread_mutex_lock (&mutex);
    printf("\nKlient %d, odkladam kufel", moj_id); 
    liczba_kufli++;
    pthread_mutex_unlock (&mutex);
  }
  return(NULL);
} 



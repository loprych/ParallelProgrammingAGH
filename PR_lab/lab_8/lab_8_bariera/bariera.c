#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>


static int ilosc_watkow_w_funkcji = 0;
static int ilosc_watkow = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t increment_lock = PTHREAD_MUTEX_INITIALIZER;

void bariera_init(int il_watkow) {
	ilosc_watkow = il_watkow;
}

void bariera (){
	pthread_mutex_lock(&increment_lock);
	ilosc_watkow_w_funkcji++;	
	pthread_mutex_unlock(&increment_lock);
	bool ostatni_watek = false;
	if (ilosc_watkow == ilosc_watkow_w_funkcji) {
		ostatni_watek = true;
		ilosc_watkow_w_funkcji = 0;
		for(int i =0; i < ilosc_watkow - 1; i++){
			pthread_cond_signal(&condition);
		}
	}
	pthread_mutex_lock(&lock);
	if (!ostatni_watek){
	pthread_cond_wait(&condition, &lock); 
	}
	pthread_mutex_unlock(&lock);
}

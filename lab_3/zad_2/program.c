#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define LICZBA_W_MAX 4

void* zadanie_watku(void* arg_wsk) {
    int moj_arg = *((int*)arg_wsk);
    pthread_t x = pthread_self();
    printf("ID systemowy: %d i identyfikator = %ld\n", moj_arg, x);
    return NULL;
}

int main() {
    pthread_t threads[LICZBA_W_MAX];
    int indeksy[LICZBA_W_MAX];
    int p = LICZBA_W_MAX;

    printf("Dzialam\n");

    for (int i = 0; i < p; i++) {
        indeksy[i] = i;
    }

    for (int i = 0; i < p; i++) {
        pthread_create(&threads[i], NULL, zadanie_watku, (void*)&indeksy[i]);
    }
    for (int i = 0; i < p; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_exit(NULL);
    printf("Dzialam\n");
}





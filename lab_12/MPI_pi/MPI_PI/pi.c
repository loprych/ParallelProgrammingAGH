#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define SCALAR double
//#define SCALAR float

#ifndef M_PI // standardy C99 i C11 nie wymagają definiowania stałej M_PI
#define M_PI (3.14159265358979323846)
#endif

int main(  int argc, char** argv  ){ 
  int max_liczba_wyrazow=0;

  int rank, ranksent, size, source, dest, tag, i;
  MPI_Status status;

  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  if(rank == 0){
    printf("Podaj maksymalną liczbę wyrazów do obliczenia przybliżenia PI\n");
    scanf("%d", &max_liczba_wyrazow);
  }

  MPI_Bcast(&max_liczba_wyrazow, 1, MPI_INT, 0, MPI_COMM_WORLD);

   int my_start = rank * ceil(1.0 * max_liczba_wyrazow / size);
   int my_stride = 1;
   int my_end = (rank + 1) * ceil(1.0 * max_liczba_wyrazow / size);
   if(my_end > max_liczba_wyrazow)
   my_end = max_liczba_wyrazow;
   
  //double t = MPI_Wtime();

  SCALAR suma_plus=0.0;
  SCALAR suma_minus=0.0;

  for(i=my_start; i<my_end; i += my_stride){
    int j = 1 + 4*i;
    suma_plus += 1.0/j;
    suma_minus += 1.0/(j+2.0);
  }


  //t = MPI_Wtime() - t;

  SCALAR my_result = suma_plus - suma_minus;

  SCALAR pi_approx;

  MPI_Reduce(&my_result, &pi_approx, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  //MPI_Allreduce(&my_result, &pi_approx, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);


  if(rank == 2) {
    printf("Proces o randze: %d\n", rank);
    pi_approx *= 4;
    printf("PI obliczone: \t\t\t%20.15lf\n", pi_approx);
    printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
   // printf("Czas obliczeń: %lf\n", t);
  }

  MPI_Finalize();
  return(0);
}

#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include "mpi.h"

struct My_struct {
	char name[6]; //6B
	double age; //8B
	int points; //4B
};

int main( int argc, char** argv ){ 
  
  int rank, ranksent, size, source, dest, tag; 
  MPI_Status status;
  
  MPI_Init( &argc, &argv ); 
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );  
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  int size_struct; //zliczanie rozmiaru pojedynczego pola w strukturze
  int packet_size; //rozmiar bufor i paczki ktora bedziemy wysylac
  int position = 0; //zapisanie gdzie skonczylismy w buforze
  MPI_Pack_size(6, MPI_CHAR, MPI_COMM_WORLD, &size_struct);
  packet_size = size_struct;
  MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &size_struct);
  packet_size += size_struct;//liczenie rozmiaru buforu, sumowanie rozmiaru podstruktur
  MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &size_struct);
  packet_size += size_struct;
  //alokacja pamieci na te dane
  void* bufor = (void* ) malloc(packet_size);
  if(size>1){
  //proces poczatkowy
  if(rank == 0){
   tag = 0; dest = 1;
   struct My_struct value = {"Lukasz", 22.5, 0};
   MPI_Pack(&value.name[0], 6, MPI_CHAR, bufor, packet_size, &position, MPI_COMM_WORLD);
   MPI_Pack(&value.age, 1, MPI_DOUBLE, bufor, packet_size, &position, MPI_COMM_WORLD);
   MPI_Pack(&value.points, 1, MPI_INT, bufor, packet_size, &position, MPI_COMM_WORLD);
   MPI_Send (&rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
   MPI_Send (bufor, position, MPI_PACKED, dest, tag+1, MPI_COMM_WORLD);
   
  }
  //wszystkie inne watki niz poczatkowy
  else{
  int prev = rank - 1;
  int next = rank + 1;
  MPI_Recv (&ranksent, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);
  MPI_Recv (bufor, 18, MPI_PACKED, prev, 1, MPI_COMM_WORLD, &status); //zapisanie do bufora 18B wysłanych
  struct My_struct value;
  MPI_Unpack (bufor, 18, &position, &value.name, 6, MPI_CHAR, MPI_COMM_WORLD);
  MPI_Unpack (bufor, 18, &position, &value.age, 1, MPI_DOUBLE, MPI_COMM_WORLD);
  MPI_Unpack (bufor, 18, &position, &value.points, 1, MPI_INT, MPI_COMM_WORLD);
  printf("proces %d, odebrał imie: %s, wiek: %f, ilosc punktow: %d od procesu %d \n",  rank, value.name, value.age, value.points, ranksent);
  //wszystkie watki srodkowe, procesy środkowe
  if(rank < size - 1) {
   position = 0; //zerujemy pozycję, bo jest ona nadpisana w unpackach podczas odpakowywania
   value.points++;
   MPI_Pack(&value.name[0], 6, MPI_CHAR, bufor, packet_size, &position, MPI_COMM_WORLD);
   MPI_Pack(&value.age, 1, MPI_DOUBLE, bufor, packet_size, &position, MPI_COMM_WORLD);
   MPI_Pack(&value.points, 1, MPI_INT, bufor, packet_size, &position, MPI_COMM_WORLD);
   MPI_Send(&rank, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
   MPI_Send(bufor, position, MPI_PACKED, next, 1, MPI_COMM_WORLD);		
  }
  //dotyczy ostatniego watku, ktory wysyla do watku pierwszego
  }
  
  }
  else{
	printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }

  
  MPI_Finalize(); 
  
  return(0);

}


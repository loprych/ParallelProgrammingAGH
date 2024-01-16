# kompilator c
CCOMP = mpicc
#CCOMP = mpicc
# konsolidator
LOADER = mpicc
#LOADER = mpicc
# program uruchomieniowy MPI
MPI_run = mpiexec -oversubscribe

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm
LIB = -lm

all: pi

run: pi
	$(MPI_run) -np 6 ./pi

# zaleznosci i komendy
pi : pi.o
	$(LOADER) $(OPT) pi.o -o pi $(LIB)

# jak uzyskac plik moj_program.o ?
pi.o: pi.c
	$(CCOMP) -c $(OPT) pi.c

clean:
	rm -f *.o pi

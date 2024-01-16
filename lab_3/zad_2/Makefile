# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

start: clean program

# zaleznosci i komendy
program: program.o 
	$(LOADER) $(OPT) program.o -o program $(LIB)

# jak uzyskac plik fork.o ?
program.o: program.c
	$(CCOMP) -c $(OPT) program.c $(INC) 

clean:
	rm -f *.o program

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
pub_sym_1: pub_sym_1.o 
	$(LOADER) $(OPT) pub_sym_1.o -o pub_sym_1 $(LIB)

# jak uzyskac plik?
pub_sym_1.o: pub_sym_1.c
	$(CCOMP) -c $(OPT) pub_sym_1.c $(INC) 

clean:
	rm -f *.o pub_sym_1

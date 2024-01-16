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
pub_sym_1_2: pub_sym_1_2.o 
	$(LOADER) $(OPT) pub_sym_1_2.o -o pub_sym_1_2 $(LIB)

# jak uzyskac plik?
pub_sym_1_2.o: pub_sym_1_2.c
	$(CCOMP) -c $(OPT) pub_sym_1_2.c $(INC) 

clean:
	rm -f *.o pub_sym_1_2

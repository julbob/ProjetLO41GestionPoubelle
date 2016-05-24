
CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -lpthread
LDFLAGS=-lpthread
EXEC=test

all: $(EXEC)

test: test.o Poubelle.o LinkedListPoubelle.o CentreDechets.o Camion.o Usager.o
	$(CC) -o $@ $^ $(LDFLAGS)

test.o: test.c Poubelle.h Camion.h Usager.h LinkedListPoubelle.h CentreDechets.h
	$(CC) -o $@ -c $< $(CFLAGS)

Poubelle.o: Poubelle.c Poubelle.h Camion.h Usager.h LinkedListPoubelle.h CentreDechets.h
	$(CC) -o $@ -c $< $(CFLAGS)

LinkedListPoubelle.o: LinkedListPoubelle.c  Poubelle.h Camion.h Usager.h LinkedListPoubelle.h CentreDechets.h
	$(CC) -o $@ -c $< $(CFLAGS)

CentreDechets.o: CentreDechets.c Poubelle.h Camion.h Usager.h LinkedListPoubelle.h CentreDechets.h
	$(CC) -o $@ -c $< $(CFLAGS)

Camion.o: Camion.c Poubelle.h Camion.h Usager.h LinkedListPoubelle.h CentreDechets.h
	$(CC) -o $@ -c $< $(CFLAGS)



Usager.o: Usager.c Poubelle.h Camion.h Usager.h LinkedListPoubelle.h CentreDechets.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)

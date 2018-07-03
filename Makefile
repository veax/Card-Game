CC=g++
CFLAGS=-W -Wall -std=c++11 -pedantic
LDFLAGS=

SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
EXEC=projet

all: $(EXEC)

projet: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

projet.o: carte.hpp jeu_de_cartes.hpp joueur.hpp pioche.hpp bataille.hpp projet.cpp
	$(CC) $(CFLAGS) -o projet.o -c projet.cpp

carte.o: carte.hpp carte.cpp
	$(CC) $(CFLAGS) -o carte.o -c carte.cpp

jeu_de_cartes.o: carte.hpp jeu_de_cartes.hpp jeu_de_cartes.cpp
	$(CC) $(CFLAGS) -o jeu_de_cartes.o -c jeu_de_cartes.cpp

joueur.o: carte.hpp joueur.hpp joueur.cpp
	$(CC) $(CFLAGS) -o joueur.o -c joueur.cpp

pioche.o: carte.hpp pioche.hpp pioche.cpp
	$(CC) $(CFLAGS) -o pioche.o -c pioche.cpp

bataille.o: carte.hpp jeu_de_cartes.hpp joueur.hpp pioche.hpp bataille.hpp bataille.cpp
	$(CC) $(CFLAGS) -o bataille.o -c bataille.cpp

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)

OBJ = gestion_matrice.o gestion_othello.o gestion_tour.o min_max_ordi.o define.h joueur.h main.o

GM = gestion_matrice.c gestion_matrice.h

GT = gestion_tour.c gestion_tour.h

MM = min_max_ordi.c min_max_ordi.h

GO = gestion_othello.c gestion_othello.h

CC = gcc

CFLAGS = -g -Wall

othello: ${OBJ}
	${CC} -o othello ${OBJ} -lm

gestion_othello.o: ${GO}
	${CC} -c gestion_othello.c ${CFLAGS}

gestion_matrice.o: ${GM}
	${CC} -c gestion_matrice.c ${CFLAGS}

gestion_tour.o: ${GT}
	${CC} -c gestion_tour.c ${CFLAGS}

min_max_ordi.o: ${MM}
	${CC} -c min_max_ordi.c ${CFLAGS}

main.o: main.c
	${CC} -c main.c ${CFLAGS}


clean :
	- rm -f *.o
	- rm -f *.exe
doc :
	doxygen doxyfile_othello

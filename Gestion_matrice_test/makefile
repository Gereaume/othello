
OBJ = gestion_matrice.o test.o
GM = gestion_matrice.c gestion_matrice.h
CC = gcc
CFLAGS = -g -Wall

test1: ${OBJ}
	${CC} -o test1 ${OBJ} -lm

gestion_matrice.o: ${GM}
	${CC} -c gestion_matrice.c ${CFLAGS}

test.o: test.c
	${CC} -c test.c ${CFLAGS}

clean :
	- rm -f *.o
	- rm -f test1

OBJ = gestion_matrice.o test_gestion_mat.o
GM = gestion_matrice.c gestion_matrice.h define.h
CC = gcc
CFLAGS = -g -Wall

test1: ${OBJ}
	${CC} -o test1 ${OBJ} -lm

gestion_matrice.o: ${GM}
	${CC} -c gestion_matrice.c ${CFLAGS}

test_gestion_mat.o: test_gestion_mat.c
	${CC} -c test_gestion_mat.c ${CFLAGS}

clean :
	- rm -f *.o
	- rm -f test1
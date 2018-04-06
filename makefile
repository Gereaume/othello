
CC=gcc
SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -I${SDLINC_DIR}  -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR} 

test_fonctions=src
OBJS=${test_fonctions}/gestion_matrice.o ${test_fonctions}/affichage.o ${test_fonctions}/sdljeu.o ${test_fonctions}/gestion_othello.o ${test_fonctions}/min_max_ordi.o ${test_fonctions}/main.o

CFLAGS = -g -Wall
PROG=sdl


sdl: ${OBJS}
	${CC} -o ${PROG} ${OBJS} ${LIBS}  -lm

main.o : ${test_fonctions}/main.c
	${CC} -c ${test_fonctions}/main.c ${LIBS} ${CFLAGS}

affichage.o : ${test_fonctions}/affichage.c ${test_fonctions}/affichage.h
	${CC} -c ${test_fonctions}/affichage.c ${LIBS} ${CFLAGS}

sdljeu.o : ${test_fonctions}/sdljeu.c ${test_fonctions}/sdljeu.h
	${CC} -c ${test_fonctions}/sdljeu.c ${LIBS} ${CFLAGS}

min_max_ordi.o: ${test_fonctions}/min_max_ordi.c ${test_fonctions}/min_max_ordi.h 
	${CC} -c ${test_fonctions}/min_max_ordi.c ${CFLAGS}

gestion_matrice.o: ${test_fonctions}/gestion_matrice.c ${test_fonctions}/gestion_matrice.h
	${CC} -c ${test_fonctions}/gestion_matrice.c ${CFLAGS}

gestion_othello.o: ${test_fonctions}/gestion_othello.c ${test_fonctions}/gestion_othello.h
	${CC} -c ${test_fonctions}/gestion_othello.c ${CFLAGS}


clean:
	rm -f ${PROG} *.o
	rm -f *.o





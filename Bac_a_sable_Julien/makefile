
CC=gcc
SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -I${SDLINC_DIR}  -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR} 

test_fonctions=Commun/Gestion_matrice_test
OBJS=${test_fonctions}/gestion_matrice.o ${test_fonctions}/gestion_othello.o ${test_fonctions}/define.h ${test_fonctions}/joueur.h ${test_fonctions}/min_max_ordi.o sdl.o

CFLAGS = -g -Wall
PROG=sdl


sdl: affichage.o sdljeu.o ${OBJS}
	${CC} -o ${PROG} affichage.o sdljeu.o ${OBJS} ${LIBS}  -lm

sdl.o : sdl.c
	${CC} -c sdl.c ${LIBS} ${CFLAGS}

affichage.o : affichage.c affichage.h
	${CC} -c affichage.c ${LIBS} ${CFLAGS}

sdljeu.o : sdljeu.c sdljeu.h
	${CC} -c sdljeu.c ${LIBS} ${CFLAGS}

min_max_ordi.o: ${test_fonctions}/min_max_ordi.c ${test_fonctions}/min_max_ordi.h 
	${CC} -c ${test_fonctions}/min_max_ordi.c ${CFLAGS}

gestion_matrice.o: ${test_fonctions}/gestion_matrice.c ${test_fonctions}/gestion_matrice.h
	${CC} -c ${test_fonctions}/gestion_matrice.c${CFLAGS}

gestion_othello.o: ${test_fonctions}/gestion_othello.c ${test_fonctions}/gestion_othello.h
	${CC} -c ${test_fonctions}/gestion_othello.c${CFLAGS}

clean:
	rm -f ${PROG} *.o
	rm -f *.o






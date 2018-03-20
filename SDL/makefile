
CC=gcc
INCLUDE_DIR=/info/etu/l2info/l2info022/Projet/othello/SDL2-2.0.7/bin/include
LIB_DIR=/info/etu/l2info/l2info022/Projet/othello/SDL2-2.0.7/bin/lib
OPTS=-L${LIB_DIR} -lSDL2 -I${INCLUDE_DIR}
PROG=sdl

all: sdl

sdl: sdl.c
	${CC} sdl.c -o ${PROG}  ${OPTS}

clean:
	rm -f ${PROG} *.o

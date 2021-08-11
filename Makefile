CC=gcc
DEBUG=-g -DDEBUG
OFLAGS=-Wall -Wshadow -c
HEADERS=-Iinclude

OBJ=./obj/
OUT=./out/
SRC=./src/

build: objects
	${CC} string.o queue.o list.o player.o units.o core.o game.o main.o -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o game
	mv ./*.o ${OBJ}
	mv ./game ${OUT}

objects:
	${CC} ${OFLAGS} ${HEADERS} ${DEBUG} ${SRC}player.c -o player.o
	${CC} ${OFLAGS} ${HEADERS} ${DEBUG} ${SRC}list.c -o list.o
	${CC} ${OFLAGS} ${HEADERS} ${DEBUG} ${SRC}queue.c -o queue.o
	${CC} ${OFLAGS} ${HEADERS} ${DEBUG} ${SRC}string.c -o string.o
	${CC} ${OFLAGS} ${HEADERS} ${DEBUG} ${SRC}units.c -o units.o
	${CC} ${OFLAGS} ${HEADERS} ${DEBUG} ${SRC}core.c -o core.o
	${CC} ${OFLAGS} ${HEADERS} ${DEBUG} ${SRC}game.c -o game.o
	${CC} ${OFLAGS} ${HEADERS} ${DEBUG} ${SRC}main.c -o main.o

clean:
	rm $(OBJ)* $(OUT)* *.o

run:
	./out/game
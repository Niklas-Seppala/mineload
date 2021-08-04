CC=gcc
DEBUG=-g -DDEBUG
OFLAGS=-Wall -Wshadow -c
HEADERS=-Iinclude

OBJ=./obj/
OUT=./out/
SRC=./src/

build:
	${CC} ${SRC}/main.c -Wall -Wshadow ${HEADERS} -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o ${OUT}game

clean:
	rm $(OBJ)* $(OUT)* *.o
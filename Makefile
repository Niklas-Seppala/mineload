CC=gcc
DEBUG=-g -DDEBUG
OFLAGS=-Wall -Wshadow -c
HEADERS=-Iinclude
RAYLIB:=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
GAME_TITLE:=mineload

COMPLETE_PRINT = \033[1;32mBuild Complete\033[0m
MODULE_PRINT = \033[0;34m$@\033[0m

OBJ_DIR=./obj/
OUT_DIR=./out/
SRC_DIR := ./src/

SRC_FILES := $(wildcard ${SRC_DIR}*.c)
SRC := $(SRC_FILES:${SRC_DIR}%=%)
OBJS := $(SRC:%.c=%.o)
BINS := $(SRC:%.c=%)

build: ${BINS}
	@echo -e "Linking..."
	@${CC} ${OBJS} ${RAYLIB} -o ${OUT_DIR}${GAME_TITLE}
	@mv ./*.o ${OBJ_DIR}
	@echo -e "$(COMPLETE_PRINT)"

	@echo -e "Execute:"
	@echo "    ${OUT_DIR}${GAME_TITLE}"
	@echo "    make run"

%.o: ${SRC_DIR}%.c
	@echo -e "Compiling module: $(MODULE_PRINT)."
	@${CC} ${OFLAGS} ${HEADERS} ${DEBUG} $< -o $@
	

%: %.o
	

clean:
	@rm $(OBJ_DIR)* $(OUT_DIR)* *.o 2>/dev/null || true

run:
	./out/mineload
ifndef VERBOSE
.SILENT:
endif

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wunreachable-code
LD_FLAGS = -lGL -lGLEW -lglfw3 -lm
OUT = main

SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

NC = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m

$(OUT) : $(OBJ)
	echo "[${RED}0%${NC}] Linking Object Files."
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LD_FLAGS)
	echo "[${GREEN}100%${NC}] Finished Linking."

%.o : %.c
	echo "[${RED}0%${NC}] Compiling $<."
	$(CC) $(CFLAGS) -c -o $@ $<
	echo "[${GREEN}100%${NC}] Finished Compiling."

clean :
	rm -f $(OUT) $(OBJ)

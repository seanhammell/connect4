CC = clang
OBJ = src/main.c src/state.c src/texture.c src/board.c
FLAGS = -g -Werror -std=c89
INC = -I .
LIBS = -l SDL2 -l SDL2_image
TARGET = connect

all: $(OBJ)
	$(CC) $(OBJ) $(FLAGS) $(INC) $(LIBS) -o $(TARGET)

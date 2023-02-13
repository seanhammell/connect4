CC = clang
OBJ = src/main.c src/state.c
FLAGS = -g -Werror
INC = -I .
LIBS = -l SDL2 -l SDL2_image
TARGET = connect

all: $(OBJ)
	$(CC) $(OBJ) $(FLAGS) $(INC) $(LIBS) -o $(TARGET)

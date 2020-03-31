COMP = gcc
FLAGS = -Wall -g -std=c99 -w -lglut -lGLU -lGL

SRC_DIR = src
SOURCE = $(wildcard $(SRC_DIR)/*.c)
OBJ_DIR = obj
OBJECT = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCE))

print-% : ; @echo $* = $($*)

Emul8tor: $(OBJECT) 
	$(COMP) $^ -o Executable $(FLAGS)


obj/%.o : $(SRC_DIR)/%.c
	$(COMP) $(FLAGS) -c $^ -o $@


clean: 
	rm obj/*
	rm Executable
	rm log.txt

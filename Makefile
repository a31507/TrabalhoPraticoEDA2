# Nome do executável final
EXEC = programa

# Diretórios e ficheiros
LIB_DIR = biblioteca
LIB_SRC = $(LIB_DIR)/estruturas2.c
LIB_OBJ = $(LIB_DIR)/estruturas2.o
LIB_A   = $(LIB_DIR)/libestruturas2.a
HEADER  = $(LIB_DIR)/estruturas2.h

# Ficheiro principal (altera se for main2.c)
MAIN = main.c

# Compilador e flags
CC = gcc
CFLAGS = -Wall -I$(LIB_DIR)
LDFLAGS = -L$(LIB_DIR) -lestruturas2 -lm

# Regra principal
all: $(EXEC)

# Compilar a biblioteca
$(LIB_A): $(LIB_OBJ)
	ar rcs $@ $^

# Compilar o objeto da biblioteca
$(LIB_OBJ): $(LIB_SRC) $(HEADER)
	$(CC) -c $(LIB_SRC) -o $(LIB_OBJ)

# Compilar o programa final
$(EXEC): $(MAIN) $(LIB_A)
	$(CC) $(MAIN) -o $(EXEC) $(CFLAGS) $(LDFLAGS)

# Limpar ficheiros gerados
clean:
	rm -f $(LIB_OBJ) $(LIB_A) $(EXEC)

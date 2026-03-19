CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJ = main.o
EXEC = pendu

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -rf *.o $(EXEC)
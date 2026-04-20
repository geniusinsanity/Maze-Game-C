CC = gcc
CFLAGS = -Wall

# Default target
all: game

# Linking
game: main.o map.o
	$(CC) $(CFLAGS) main.o map.o -o game.exe

# Compiling main.c
main.o: main.c map.h
	$(CC) $(CFLAGS) -c main.c

# Compiling map.c
map.o: map.c map.h
	$(CC) $(CFLAGS) -c map.c

# Clean object files and executables
clean:
	del /Q *.o game.exe 2>nul

# Run the program
run: game
	.\game.exe

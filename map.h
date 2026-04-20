#ifndef MAP_H
#define MAP_H

#define MAX_SIZE 31 // Max grid size (must be odd for maze algorithm)

// ANSI Color Codes for terminal output
#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

// Map cell values
#define EMPTY 0
#define WALL 1
#define PLAYER 2
#define EXIT 3

// Function prototypes
void initMap(int map[MAX_SIZE][MAX_SIZE], int row, int clm);
void displayMap(int map[MAX_SIZE][MAX_SIZE], int row, int clm, int level, int score);

#endif // MAP_H
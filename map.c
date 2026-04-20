#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "map.h"

// ============================================================
// shuffle() - Randomly shuffles an array of integers
// Used to randomize the direction order for maze carving
// ============================================================
void shuffle(int array[], int n) {
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        int t = array[i];
        array[i] = array[j];
        array[j] = t;
    }
}

// ============================================================
// carveMaze() - Recursive Backtracker Algorithm (DFS)
// Carves corridors through a grid of walls to create a real maze
// It jumps 2 cells at a time, breaking the wall in between
// ============================================================
void carveMaze(int map[MAX_SIZE][MAX_SIZE], int x, int y, int row, int clm) {
    // Direction vectors: each moves 2 cells (up, down, left, right)
    int dx[] = {0, 0, -2, 2};
    int dy[] = {-2, 2, 0, 0};
    int dirs[] = {0, 1, 2, 3};
    shuffle(dirs, 4); // Randomize direction order for unique mazes

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[dirs[i]];
        int ny = y + dy[dirs[i]];

        // Check bounds and ensure the target cell is still a wall (unvisited)
        if (nx > 0 && nx < row - 1 && ny > 0 && ny < clm - 1 && map[nx][ny] == WALL) {
            // Break the wall between current cell and target cell
            map[x + dx[dirs[i]] / 2][y + dy[dirs[i]] / 2] = EMPTY; 
            map[nx][ny] = EMPTY; // Mark target cell as a corridor
            carveMaze(map, nx, ny, row, clm); // Recurse from the new cell
        }
    }
}

// ============================================================
// initMap() - Initializes the maze grid
// 1. Fills the entire grid with walls
// 2. Carves corridors using DFS (Recursive Backtracker)
// 3. Places the Player at the top entrance and Exit at the bottom
// ============================================================
void initMap(int map[MAX_SIZE][MAX_SIZE], int row, int clm) {
    // Step 1: Fill the entire grid with walls
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < clm; j++) {
            map[i][j] = WALL;
        }
    }

    // Step 2: Start carving from cell (1,1) inside the border
    map[1][1] = EMPTY;
    carveMaze(map, 1, 1, row, clm);

    // Step 3: Place the Player (top entrance) and Exit (bottom exit)
    map[0][1] = PLAYER; 
    map[row-1][clm-2] = EXIT; 
}

// ============================================================
// resetCursor() - Moves console cursor back to position (0,0)
// This overwrites the previous frame instead of clearing the screen,
// which eliminates all screen flickering during gameplay
// ============================================================
void resetCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(hOut, pos);
}

// ============================================================
// displayMap() - Renders the maze with a decorative UI frame
// Uses resetCursor() for flicker-free redrawing every frame
// ============================================================
void displayMap(int map[MAX_SIZE][MAX_SIZE], int row, int clm, int level, int score) {
    resetCursor(); 
    
    // Game title and score bar
    printf("\n\t" CYAN "=== THE MAZE GAME ===" RESET "\n");
    printf("\t" YELLOW "Level: %d    Score: %d" RESET "\n\n", level, score);

    // Top border
    printf("\t" BLUE "╔");
    for (int j = 0; j < clm; j++) printf("══");
    printf("╗\n" RESET);

    // Map content with side borders
    for (int i = 0; i < row; i++) {
        printf("\t" BLUE "║" RESET); 
        for (int j = 0; j < clm; j++) {
            if (map[i][j] == WALL) {
                printf(RED "██" RESET);       // Red wall block
            } else if (map[i][j] == PLAYER) {
                printf(GREEN "██" RESET);     // Green player block
            } else if (map[i][j] == EXIT) {
                printf(MAGENTA "██" RESET);   // Magenta exit block
            } else if (map[i][j] == EMPTY) {
                printf("  ");                 // Empty corridor (2 spaces)
            }
        }
        printf(BLUE "║\n" RESET); 
    }

    // Bottom border
    printf("\t" BLUE "╚");
    for (int j = 0; j < clm; j++) printf("══");
    printf("╝\n\n" RESET);
    
    // Control instructions
    printf("\t" YELLOW "[W/A/S/D]" RESET " : Move  |  ");
    printf(RED "[Esc]" RESET " : Quit\n");
}

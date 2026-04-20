#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h> // For _getch() - reads a key without requiring Enter
#include "map.h"

// ============================================================
// main() - Entry point of the Maze Game
// Manages the level loop, player movement, scoring, and sounds
// ============================================================
int main (void)
{
    SetConsoleOutputCP(CP_UTF8); // Enable UTF-8 output for special characters
    srand((unsigned)time(NULL)); // Seed the random number generator

    int level = 1;
    int score = 0;
    
    // Maze dimensions must be ODD numbers for the Recursive Backtracker to work correctly
    int row = 9; 
    int clm = 9; 

    // ==================== LEVEL LOOP ====================
    // Each iteration generates a new, harder maze
    while (1) { 
        system("cls"); // Full clear before generating the maze
        printf("\n\t" YELLOW "Generating Level %d... Please wait." RESET "\n", level);
        
        int gameMap[MAX_SIZE][MAX_SIZE];
        initMap(gameMap, row, clm); // Generate a guaranteed-solvable maze using DFS
        
        int px = 0, py = 1; // Player starts at the top entrance
        
        system("cls"); // Clear the "generating" message before gameplay starts

        // ==================== GAME LOOP ====================
        // Each iteration: draw -> check win -> read input -> move
        while (1) { 
            displayMap(gameMap, row, clm, level, score);

            // --- Win Condition: Player reached the exit ---
            if (px == row - 1 && py == clm - 2) {
                // Victory sound melody
                Beep(523, 100); // C5
                Beep(659, 100); // E5
                Beep(784, 100); // G5
                Beep(1046, 300); // C6
                
                score += (level * 10); // Higher levels = more points
                
                printf("\n\t" GREEN "Level %d Cleared!" RESET "\n", level);
                Sleep(1500); // Pause to let the player see the message
                
                // --- Increase difficulty for the next level ---
                level++;
                row += 2; // Maze grows by 2 (keeps it odd)
                clm += 2;
                if (row > MAX_SIZE) row = MAX_SIZE; // Cap at maximum size
                if (clm > MAX_SIZE) clm = MAX_SIZE;
                
                break; // Exit game loop -> go to next level
            }

            // --- Read player input (no Enter key needed) ---
            char move = _getch();
            
            int nx = px; // Next X position (calculated before validation)
            int ny = py; // Next Y position

            // Arrow keys send 2 bytes: first is 224 (or 0), second is the scancode
            if (move == -32 || move == 0) { // 0xE0 = -32 (signed) or 224 (unsigned)
                move = _getch(); // Read the actual arrow scancode
                if (move == 72) nx--;       // Arrow Up
                else if (move == 80) nx++;  // Arrow Down
                else if (move == 75) ny--;  // Arrow Left
                else if (move == 77) ny++;  // Arrow Right
            }
            else if (move == 'w' || move == 'W') nx--;      // W = Up
            else if (move == 's' || move == 'S') nx++;       // S = Down
            else if (move == 'a' || move == 'A') ny--;       // A = Left
            else if (move == 'd' || move == 'D') ny++;       // D = Right
            else if (move == 27) {                            // Esc = Quit
                system("cls");
                printf("\n\t" RED "Game Over!" RESET "\n");
                printf("\t" YELLOW "Final Score: %d" RESET "\n\n", score);
                Beep(400, 300); Beep(300, 500); // Sad exit sound
                return 0; 
            }

            // --- Validate movement (within bounds and not a wall) ---
            if (nx >= 0 && nx < row && ny >= 0 && ny < clm) {
                if (gameMap[nx][ny] != WALL) { 
                    gameMap[px][py] = EMPTY;  // Clear old position
                    px = nx;                   // Update player X
                    py = ny;                   // Update player Y
                    gameMap[px][py] = PLAYER;  // Set new position
                    Beep(800, 30);             // Short movement beep
                } else {
                    Beep(150, 80);             // Wall collision buzz
                }
            }
        }
    }

    return 0;
}
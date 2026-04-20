# 🎮 Advanced Maze Game in C

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgray.svg)
![Build](https://img.shields.io/badge/Build-Makefile-orange.svg)

Welcome to the **Advanced Maze Game**, a professional-grade, multi-level console maze game developed entirely in C. This project is built to explore and implement advanced data structure concepts, algorithms, and optimized console rendering techniques.

## ✨ Features

- **Algorithmic Generation**: Uses **Depth-First Search (DFS)** to dynamically generate random maps while guaranteeing 100% solvability.
- **Dynamic Level System**: Progressive difficulty scaling to face larger and more complex mazes as you advance.
- **High-Performance Console UI**: Built with a specialized rendering engine to ensure flicker-free, smooth frame updates directly in your terminal.
- **Immersive Audio**: Integrated native Windows API sound effects to bring the game to life.
- **Clean Architecture**: Highly modular C codebase separating algorithms (`map.c`/`map.h`) from the main game loop (`main.c`).

## 🛠️ Prerequisites

To compile and run this game, you'll need:
- A C compiler like GCC (MinGW on Windows).
- `make` utility for utilizing the provided `Makefile`.
- **Windows Environment**: Recommended, since the game leverages the Windows API for high-performance console operations and audio.

## 🚀 How to Run

1. **Clone the repository**:
   ```bash
   git clone https://github.com/geniusinsanity/Maze-Game-C.git
   cd "Maze Game using C"
   ```

2. **Build the project**:
   Use `make` to compile the source code cleanly:
   ```bash
   make
   ```

3. **Start the game**:
   Run the generated executable:
   ```bash
   ./maze.exe
   ```
   *(Note: The exact executable name depends on your Makefile configuration, typically `main.exe` or similar).*

## 🎮 Controls

- `W`, `A`, `S`, `D` or **Arrow Keys** — Move your character.
- `ESC` — Exit / Return to menu.

## 📚 Documentation

For an in-depth dive into the internal logic, state management, algorithm implementation (DFS), and overall architecture, please refer to the included documents:
- `The Maze Game - Full Documentation.pdf`
- `documentation.html`

---
*Developed with ❤️ as part of the ADS (Advanced Data Structures) Course.*

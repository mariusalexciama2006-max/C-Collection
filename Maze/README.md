# Maze

## About
This project is a lightweight, terminal-based Maze Generator and Solver written entirely in C. It procedurally generates a perfect maze using a randomized Depth-First Search (DFS) algorithm and solves it by finding the shortest path to a user-defined target using Breadth-First Search (BFS). 
## Features
*   **Procedural Maze Generation:** Creates random, perfectly solvable mazes using a custom dynamic Stack.
*   **Shortest Pathfinding:** Uses a custom Queue to perform Breadth-First Search (BFS), ensuring the quickest route from the start to your chosen target.
*   **Visual Terminal Output:** Renders the maze directly in the console and highlights the calculated shortest path using ANSI color codes.

## Requirements
To compile and run this project, you will need:
*   A C compiler installed on your system (e.g., `gcc`, `clang`, or MSVC).
*   A terminal or command prompt that supports ANSI escape codes (to properly display the green path).

## How to Run

1. **Save the code:** Save the provided C code into a file named `maze.c`.
2. **Compile the program:** Open your terminal, navigate to the folder where you saved the file, and compile it:
   ```bash
   gcc maze.c -o maze

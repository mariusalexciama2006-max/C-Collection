# C-Collection

## About

This repository contains a collection of C programming projects that I have built to practice and improve my software development skills. Rather than just storing the code, each project folder contains its own documentation explaining the logic, algorithms, and how to compile and run the programs. 

The objective of this repository is to build a structured portfolio of C projects while continuously improving my understanding of memory management, data structures, and procedural programming.

---

## Repository Structure

```text
C-Collection/
├── Maze/
├── .gitignore
└── README.md
```

## Projects

| Project | Difficulty | Type | Summary |
| :--- | :---: | :---: | :--- |
| [Maze](./Maze/) | 🟡 Intermediate | Game / Algorithm | Generates random mazes and finds the shortest path using custom stacks and queues |

---

## Concepts Covered

* **Custom Data Structures:** Implementing dynamic Stacks and Circular Queues from scratch using structs and pointers.
* **Algorithmic Logic:** 
  * Using Randomized Depth-First Search (DFS) for procedural maze generation.
  * Using Breadth-First Search (BFS) for shortest-path finding.
* **Memory Management:** Dynamically allocating and deallocating memory (`malloc`, `calloc`, `free`) to prevent memory leaks in custom data structures.
* **Grid Mathematics:** Manipulating 2D arrays/matrices for coordinate mapping and boundary checking.
* **Terminal UI & Randomization:** Using ANSI escape codes for colored terminal rendering, and standardizing randomization (`<time.h>`, `rand()`) for shuffling directional logic.

---

## Tools & Libraries

* C Programming
* Standard C Library (`stdio.h`, `stdlib.h`,  `time.h`)
* GNU Compiler Collection (GCC)
* Git & GitHub

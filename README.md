# Search Algorithms

This repository contains implementations of various search algorithms in C++.

## Compilation

To compile all the C++ files, you can use the provided `Makefile`.

To compile all the files, run the following command:

```bash
make
```

This will create an executable for each `.cpp` file in the current directory. The executables will have the same name as the `.cpp` file, with a `.out` extension. For example, `1_british_museum.cpp` will be compiled to `1_british_museum.out`.

To compile a single file, you can run the following command:

```bash
g++ -std=c++17 -Wall <filename>.cpp -o <filename>.out
```

For example, to compile `1_british_museum.cpp`, you would run:

```bash
g++ -std=c++17 -Wall 1_british_museum.cpp -o 1_british_museum.out
```

## Running the Executables

To run an executable, you can use the `run-%` rule in the `Makefile`. For example, to run `1_british_museum.out`, you would run:

```bash
make run-1
```

This will run the first file in the directory that matches the `*.cpp` pattern. To run a specific file, you can use the number of the file in the directory. For example, to run the 5th file, you would run:

```bash
make run-5
```

Alternatively, you can run the executables manually:

```bash
./<filename>.out
```

For example, to run `1_british_museum.out`, you would run:

```bash
./1_british_museum.out
```

## Implemented Algorithms

The following search algorithms are implemented in this repository:

*   **1_british_museum.cpp**: Implements the British Museum search algorithm. This is a brute-force search that explores all possible paths.
*   **2_bfs.cpp**: Implements the Breadth-First Search (BFS) algorithm.
*   **3_dfs.cpp**: Implements the Depth-First Search (DFS) algorithm.
*   **4_bfs_dfs.cpp**: Implements Iterative Deepening Depth-First Search (IDDFS).
*   **5_bfs_history.cpp**: Implements BFS with a history of visited nodes to avoid cycles.
*   **6_dfs_history.cpp**: Implements DFS with a history of visited nodes and dead-end detection.
*   **7_hill_climbing.cpp**: Implements the Hill Climbing search algorithm.
*   **8_beam_search.cpp**: Implements the Beam Search algorithm.
*   **9_hill_climbing_history.cpp**: Implements Hill Climbing with a history of visited nodes.
*   **10_beam_search_history.cpp**: Implements Beam Search with a history of visited nodes.
*   **11_oracle.cpp**: Implements an "oracle" search, which is essentially a brute-force search that finds the optimal path. This is used as a baseline for comparison with other algorithms.
*   **12_branch_and_bound.cpp**: Implements the Branch and Bound algorithm.
*   **13_branch_and_bound_EH.cpp**: Implements Branch and Bound with an extended heuristic.
*   **14_branch_and_bound_EL.cpp**: Implements Branch and Bound with an early exit.
*   **15_a_star.cpp**: Implements the A* search algorithm.
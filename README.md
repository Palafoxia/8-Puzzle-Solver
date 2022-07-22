# 8-PUZZLE SOLVER | C++ ARTIFICIAL INTELLIGENCE

This project implements Uniform Cost and A* search algorithms in C++ to solve 8-puzzles.
We can use the algorithms to solve any solvable 8-puzzle, including sample puzzles given in `node.cpp`
These "test cases" are all solvable and of solution depth 0, 2, 4, 8, 12, 16, 20, and 24.

An 8-puzzle is represented as a 2D 3x3 vector where each numbered tile is represented by itself, and the empty tile is represented by 0.
A "solved" or goal state of an 8-puzzle is achieved when each number goes in a sequential order as follows: <br>
1 &nbsp; 2 &nbsp; 3 <br>
4 &nbsp; 5 &nbsp; 6 <br>
7 &nbsp; 8 &nbsp; 0

A move is defined as swapping the empty tile (0) with any cardinally adjacent tile.
The Uniform Cost search algorithm assigns the cost of every move to 1. 
The A* search algorithms utilize misplaced tile and manhattan distance heuristics to calculate the cost of a move.
All algorithms can solve 8-puzzles optimally but perform with varying efficiency.

The project report below further details the project's design and compares the performance of the algorithms on the sample puzzles.

## Running the Application
To run the application, simply run the `main.exe` file.
You can also compile the source code files manually in the IDE of your choice.

The application asks the user which puzzle they'd like to solve.
It then prints out the solution depth and total number of expanded nodes for each algorithm on the chosen puzzle.
The application will display "No solution" if the chosen puzzle is not solvable.

Note that if depth >= 16, the application won't perform Uniform Cost search.
If depth >= 24, A* search w/ the misplaced tile heuristic won't be performed.
These limitations are in place because otherwise, the algorithms won't run to completion in a reasonable time.

## Project Structure
- `algorithms.cpp/h` in `src/` contains the Uniform Cost and A* search algorithms
- `node.cpp/h` in `src/` contains the node class including sample puzzles and functions for operators and heuristics
- `main.cpp/h` in `src/` runs all the algorithms on a user-specified puzzle

# PROJECT REPORT
## Introduction
In this project, my task is to implement a uniform cost search algorithm as well as 2 A* algorithms to solve several 8-puzzles.
The 8-puzzles given are all solvable and are of 0, 2, 4, 8, 12, 16, 20, and 24 depth.
A "solved" or goal state of an 8-puzzle is achieved when each number goes in a sequential order as follows: <br>
1 &nbsp; 2 &nbsp; 3 <br>
4 &nbsp; 5 &nbsp; 6 <br>
7 &nbsp; 8 &nbsp; 0

All 3 of the algorithms are able to solve the puzzles optimally.
However, solving the 8-puzzles of higher depths requires the use of more efficient algorithms because of time and space limitations.
I set a 15-minute time limit when running an algorithm on a Ryzen 5600x.
If an algorithm can’t solve the given puzzle within that time, the algorithm is said to be unable to solve that particular puzzle.

The algorithms are written in C++ in the Visual Studio IDE.
The total number of expanded nodes are used as a metric to compare the efficiency of each algorithm.
When available, the process memory and runtime from the Diagnostic Tools tab in Visual Studio are compared as well.

## Design
The 8-puzzle is designed in C++ as a 2D 3x3 vector.
Each numbered tile is represented by itself, and the empty tile is represented by 0.

The operators used to manipulate the 8-puzzle “move” the empty tile up, down, left, or right by 1 tile.
Within the vector, these operators swap the positions between the empty tile (0) and the corresponding cardinally adjacent tile.
Any time one of these operators are executed, there is a check to see if the operation is legal.
If so, the operator returns the new puzzle.
Otherwise, an “empty” puzzle is returned with all empty tiles.

The algorithms rely on the node class defined in `node.cpp`.
All nodes consist of a 2D 3x3 vector puzzle, a depth, and values for the misplaced and Manhattan Distance heuristics.
The nodes also contain row and col fields that determine where the empty tile is located within the puzzle vector.
Children are not hard coded within the node class.
Instead, new node objects are created when necessary.

It should also be noted that nodes that are illegal moves and visited nodes do not expand and don't contribute to the total number of expanded nodes.
This also improves the performance of each algorithm by lowering the average branching factor by a significant amount.

## Comparison of Algorithms
### Uniform Cost Search
Uniform cost search for the 8-puzzle is functionally identical to a breadth-first search.
This is because the cost of any operator (or transition from one level of the tree to another) is always 1.
It can also be said that the total cost of reaching a node is equal to its depth.

Uniform cost search will expand the node with the smallest cost.
In this case, it expands each node from left to right level by level just like breadth first search.
This is the least efficient of the 3 algorithms.

### A* Search - Misplaced Tile Heuristic
The first A* search algorithm implemented uses the misplaced tile heuristic.
Any tile in the puzzle that is not in the correct position adds 1 to the value of this heuristic (not counting the empty tile).

Adding this heuristic combined with the cost of reaching a node will create the complete heuristic for an A* search.
Only using the misplaced tile heuristic creates a Hill-Climbing or Greedy algorithm that may lead to very slow and memory heavy results.
The misplaced tile heuristic A* search is the 2nd most efficient algorithm of the 3.

### A* Search - Manhattan Distance Heuristic
The second A* search algorithm implemented uses the Manhattan Distance Heuristic.
This heuristic takes the “Manhattan Distance” between the current position of a tile and position it would be at in the goal state.
The Manhattan Distance value is the sum of the distance from the puzzle’s goal state horizontal position and its goal state vertical position for each tile (not counting the empty tile).

For example, take this 8-puzzle: <br>
1 &nbsp; 2 &nbsp; 3 <br>
5 &nbsp; 0 &nbsp; 6 <br>
4 &nbsp; 7 &nbsp; 8

The 1, 2, 3, and 6 tiles are all in their goal state positions, so they add 0 to the Manhattan Distance heuristic.
The 5, 7, and 8 tiles are 1 horizontal space away from their goal state (total = 3).
The 4 tile is 1 vertical space away from its goal state (total = 4).
So the total Manhattan Distance heuristic value is 4 for this 8-puzzle.

As with any A* search algorithm, we add the cost to get to a node to the total heuristic value.
In the case of solving 8-puzzles, we add the depth of the current node to the heuristic.
This total is the true Manhattan Distance heuristic value for A* search.
This the most efficient of the 3 algorithms.

## Analyzing Performance on Sample Puzzles
These are all the sample puzzles given and their corresponding optimal depths.

<img src="images/Sample Puzzles.png" alt="drawing" width="800"/>

The first puzzle with depth 0 is the goal state and used for testing purposes.
With the rest of the puzzles, we can observe that the algorithms perform similarly when the search depth is low.
However, when the depth increases, the efficiency of the algorithms become drastically different.

The uniform cost and A* with misplaced tile heuristic searches don’t reach to the end of the solution depth axis because they were unable to solve those puzzles in a reasonable time (15 mins).
As we can clearly see, those searches would have grown their nodes expanded value exponentially, making it infeasible to solve puzzles larger than listed.

<img src="images/Nodes Expanded vs Solution Depth.png" alt="drawing" width="800"/>

## Visual Studio Diagnostic Tools Data
_Note: Columns marked as "N/A" denotes that the algorithm was not able to finish within 15 minutes for that puzzle_

### Uniform Cost Search
|  **Puzzle Depth**  |   0   |   2   |  4  |  8  |  12   | 16  | 20  | 24  |
|:------------------:|:-----:|:-----:|:---:|:---:|:-----:|:---:|:---:|:---:|
| **Expanded Nodes** |   0   |   7   | 33  | 311 | 2328  | N/A | N/A | N/A |
| **Process Memory** | 933KB | 946KB | 1MB | 2MB | 7.5MB | N/A | N/A | N/A |
|    **Runtime**     |  ~0s  |  ~0s  | ~0s | ~0s |  34s  | N/A | N/A | N/A |

### A* Search - Misplaced Tile Heuristic
|  **Puzzle Depth**  |  0   |  2   |  4   |  8   |  12  |  16   |  20  | 24  |
|:------------------:|:----:|:----:|:----:|:----:|:----:|:-----:|:----:|:---:|
| **Expanded Nodes** |  0   |  5   |  10  |  35  | 214  | 1083  | 5097 | N/A |
| **Process Memory** | <1MB | <1MB | <1MB | <1MB | <1MB | 4.5MB | 16MB | N/A |
|    **Runtime**     | ~0s  | ~0s  | ~0s  | ~0s  | ~0s  |  8s   | 174s | N/A |

### A* Search - Manhattan Distance Heuristic
|  **Puzzle Depth**  |  0   |  2   |  4   |  8   |  12  |  16  | 20  |  24  |
|:------------------:|:----:|:----:|:----:|:----:|:----:|:----:|:---:|:----:|
| **Expanded Nodes** |  0   |  5   |  10  |  24  |  64  | 382  | 729 | 6412 |
| **Process Memory** | <1MB | <1MB | <1MB | <1MB | <1MB | <1MB | 3MB | 19MB |
|    **Runtime**     | ~0s  | ~0s  | ~0s  | ~0s  | ~0s  | ~1s  | 4s  | 282s |

## Conclusion
The results found highlight the importance of using an efficient algorithm in searches to create better and faster AI.
The algorithms in increasing order of efficiency were uniform cost search, A* with the misplaced tile heuristic, and A* with the Manhattan Distance heuristic.
The 2 A* algorithms mostly differed at higher depths, showcasing how a better heuristic with the same overall algorithm can still have a significant effect on efficiency and performance.

These results are to be expected as the time and space complexity for the uniform cost search is O(bd) where b is the branching factor and d is the depth.
Meanwhile, the time and space complexities for A* search are O(bd) and O(bd), respectively, and depending on the heuristic.

It’s clear why uniform cost search is unable to perform at higher depths and why its complexities increase exponentially.
The time complexity can range to near exponential if the heuristic is not efficient, further supporting the importance of an efficient heuristic especially at asymptotic depth values.

### Trace of Uniform Cost Search (Puzzle 2)
<img src="images/Uniform Cost Search Trace.jpg" alt="drawing" width="800"/>

Each line between tree levels with 1 dash denotes a repeated node.
A line with 2 dashes denotes an illegal move.

We start at the root node and traverse our way down in a breadth-first fashion.
A significant amount of nodes are skipped, reducing our total expanded nodes down to 7.
There isn’t much in terms of optimization here.


### Trace of A* Search w/ Misplaced Tile Heuristic (Puzzle 2)
<img src="images/A-Star Search Trace.jpg" alt="drawing" width="800"/>

Each line between tree levels with 1 dash denotes a repeated node.
A line with 2 dashes denotes an illegal move.
m is the misplaced tile heuristic plus the cost to get to the node (depth).

Here, we expand all nodes from the root but decide to traverse through the right node because it has the lowest m.
We expand all of its nodes until we find the goal state, which also happens to have the lowest m.
This algorithm has 5 total expanded nodes rather than uniform cost search’s 7.

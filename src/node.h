#pragma once
#include <vector>
using namespace std;

// NODE CLASS
class node {
    private:
        vector<vector<int>> puzzle; // Each node is a puzzle
        int depth, misplaced, fn, row, col; // Depth, heuristic values, position of 0

    public:
        // GOAL STATE 8-PUZZLE
        static vector<vector<int>> solved;

        // Empty Puzzle (All 0's)
        static vector<vector<int>> emptyPuzzle; // "Empty Puzzle" (all 0's)
        
        // CONSTRUCTORS
        node(); // Construct a solved puzzle by default
        node(vector<vector<int>>, int); // Construct node (vector<vector>> puzzle, int depth)
        node(vector<vector<int>>); // Construct root node (depth = 0)

        // HEURISTICS
        int misplacedHeuristic(); // Calculate the misplaced heuristic value
        int manhattanDistance(); // Calculate the manhattan distance

        // OTHER FUNCTIONS
        bool isGoalState(); // Check if puzzle is the goal state
        bool isEmptyPuzzle(); // Check if puzzle is emptyPuzzle
        void setRowCol(); // Find the position (row, col) of 0 in the puzzle

        // OPERATORS, return emptyPuzzle if move is invalid
        vector<vector<int>> up();
        vector<vector<int>> down();
        vector<vector<int>> left();
        vector<vector<int>> right();

        // ACCESSORS
        vector<vector<int>> getPuzzle();
        int getDepth();
        int getMisplaced();
        int getFn();
        int getRow();
        int getCol();
};
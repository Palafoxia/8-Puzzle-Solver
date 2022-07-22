#pragma once

#include <vector>

using namespace std;

class node {
    private:
        vector<vector<int>> puzzle; // Each node has a puzzle
        int depth, misplaced, fn, row, col; // Depth, heuristics, 0 position

    public:
        // Test cases of varying depth
        static vector<vector<int>> solved;
        static vector<vector<int>> puzzle2;
        static vector<vector<int>> puzzle4;
        static vector<vector<int>> puzzle8;
        static vector<vector<int>> puzzle12;
        static vector<vector<int>> puzzle16;
        static vector<vector<int>> puzzle20;
        static vector<vector<int>> puzzle24;
        static vector<vector<int>> emptyPuzzle;
        
        // Constructors
        node(); // Construct a solved puzzle by default
        node(vector<vector<int>>, int); // Construct node given puzzle and depth

        // Heuristics
        int misplacedHeuristic(); // Calculate the misplaced heuristic value
        int manhattanDistance(); // Calculate the manhattan distance

        // Other Functions
        void printPuzzle(); // Print puzzle
        bool isGoalState(); // Check if puzzle is the goal state
        bool isEmptyPuzzle(); // Check if puzzle is emptyPuzzle
        void setRowCol(); // Find the position (row, col) of 0 in the puzzle

        // Operators (Move Blank 0), return emptyPuzzle if move is invalid
        vector<vector<int>> up();
        vector<vector<int>> down();
        vector<vector<int>> left();
        vector<vector<int>> right();

        // Accessors
        vector<vector<int>> getPuzzle();
        int getDepth();
        int getMisplaced();
        int getFn();
        int getRow();
        int getCol();
};
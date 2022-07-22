#include "node.h"

#include <iostream>

// TEST CASES
// Depth 0 (Reference)
vector<vector<int>> node::solved = {
	{1, 2, 3},
	{4, 5, 6},
	{7, 8, 0}
};

// Depth 2
vector<vector<int>> node::puzzle2 {
	{1, 2, 3},
	{4, 5, 6},
	{0, 7, 8}
};

// Depth 4
vector<vector<int>> node::puzzle4 {
	{1, 2, 3},
	{5, 0, 6},
	{4, 7, 8}
};

// Depth 8
vector<vector<int>> node::puzzle8 {
	{1, 3, 6},
	{5, 0, 2},
	{4, 7, 8}
};

// Depth 12
vector<vector<int>> node::puzzle12 {
	{1, 3, 6},
	{5, 0, 7},
	{4, 8, 2}
};

// Depth 16
vector<vector<int>> node::puzzle16 {
	{1, 6, 7},
	{5, 0, 3},
	{4, 8, 2}
};

// Depth 20
vector<vector<int>> node::puzzle20 {
	{7, 1, 2},
	{4, 8, 5},
	{6, 3, 0}
};

// Depth 24
vector<vector<int>> node::puzzle24 {
	{0, 7, 2},
	{4, 6, 1},
	{3, 5, 8}
};

// "Empty" Puzzle (will not expand)
vector<vector<int>> node::emptyPuzzle = {
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};

// Default Constructor, "Solved"
node::node() {
	this->puzzle = solved;
    this->depth = 0;
	this->setRowCol();
}

// Constructor
node::node(vector<vector<int>> puzzle, int depth) {
    this->puzzle = puzzle;
    this->depth = depth + 1;
    this->misplaced = depth + this->misplacedHeuristic();
    this->fn = depth + this->manhattanDistance();
	this->setRowCol();
}

// MISPLACED TILE HEURISTIC
int node::misplacedHeuristic() {
    int numMisplaced = 0;

    // For each tile in puzzle
    for(int i = 0; i < 3; i++) {
   		for (int j = 0; j < 3; j++) {
		    // Add 1 if tile in puzzle != to solved reference
		    if (puzzle[i][j] != node().puzzle[i][j]) {
			    numMisplaced++;
   			}
	    }
    }
    return numMisplaced;
}

//MANHATTAN DISTANCE HEURISTIC
int node::manhattanDistance() {
  	int distance = 0;

    //For each tile in puzzle
    for (int i = 0; i < 3; i++) {
   		for (int j = 0; j < 3; j++) {
		    if (puzzle[i][j] != 0) { //Don't calculate distance for the blank
   				//Compare to each tile in reference
    			for (int k = 0; k < 3; k++) {
   					for (int l = 0; l < 3; l++) {
					    //Once found, add distance to total
					    if (puzzle[i][j] == node().puzzle[k][l])
   							distance += abs(i - k) + abs(j - l); //Distance horizontally + vertically
    				}
	    		}
   			}
	    }
    }
    return distance;
}

// Print Puzzle
void node::printPuzzle() {
	for (int i = 0; i < puzzle.size(); i++) {
		cout << "| ";
		for (int j = 0; j < puzzle[i].size(); j++) {
			cout << puzzle[i][j] << " ";
		}
		cout << "|" << endl;
	}
	cout << endl;
}

// Check if puzzle is the goal state
bool node::isGoalState() {
	if (puzzle == solved) {
    	return true;
	} else {
	    return false;
	}
}

// Check if puzzle is empty puzzle
bool node::isEmptyPuzzle() {
	if (puzzle == emptyPuzzle) {
		return true;
	} else {
		return false;
	}
}

// Find the position (row, col) of 0 in the puzzle
void node::setRowCol() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (puzzle[i][j] == 0) {
				row = i;
				col = j;
			}
		}
	}
}

// OPERATORS
// Blank space (0) up
vector<vector<int>> node::up() {
	vector<vector<int>> newPuzzle = puzzle;
	if (row > 0) {
		newPuzzle[row][col] = newPuzzle[row - 1][col];
		newPuzzle[row - 1][col] = 0;
	} else {
		return emptyPuzzle;
	}
	return newPuzzle;
}

// Blank space (0) down
vector<vector<int>> node::down() {
	vector<vector<int>> newPuzzle = puzzle;
	if (row < newPuzzle.size() - 1) {
		newPuzzle[row][col] = newPuzzle[row + 1][col];
		newPuzzle[row + 1][col] = 0;
	} else {
		return emptyPuzzle;
	}
	return newPuzzle;
}

// Blank space (0) left
vector<vector<int>> node::left() {
	vector<vector<int>> newPuzzle = puzzle;
	if (col > 0) {
		newPuzzle[row][col] = newPuzzle[row][col - 1];
		newPuzzle[row][col - 1] = 0;
	} else {
		return emptyPuzzle;
	}
	return newPuzzle;
}

// Blank space (0) right
vector<vector<int>> node::right() {
	vector<vector<int>> newPuzzle = puzzle;
	if (col < newPuzzle[0].size() - 1) {
		newPuzzle[row][col] = newPuzzle[row][col + 1];
		newPuzzle[row][col + 1] = 0;
	} else {
		return emptyPuzzle;
	}
	return newPuzzle;
}

// Accessors
vector<vector<int>> node::getPuzzle() {return puzzle;}
int node::getDepth() {return depth;}
int node::getMisplaced() {return misplaced;}
int node::getFn() {return fn;}
int node::getRow() {return row;}
int node::getCol() {return col;}
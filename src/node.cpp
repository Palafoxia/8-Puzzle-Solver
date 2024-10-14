#include "node.h"
#include <iostream>

// GOAL STATE
vector<vector<int>> node::solved = {
	{1, 2, 3},
	{4, 5, 6},
	{7, 8, 0}
};

// EMPTY PUZZLE
vector<vector<int>> node::emptyPuzzle = {
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};

// DEFAULT CONSTRUCTOR (GOAL STATE)
node::node() {
	this->puzzle = solved;
    this->depth = 0;
	this->setRowCol();
}

// CONSTRUCTOR
node::node(vector<vector<int>> puzzle, int depth) {
    this->puzzle = puzzle;
    this->depth = depth + 1;
    this->misplaced = this->depth + this->misplacedHeuristic();
    this->fn = this->depth + this->manhattanDistance();
	this->setRowCol();
}

// ROOT NODE CONSTRUCTOR (DEPTH = 0)
node::node(vector<vector<int>> puzzle) {
	this->puzzle = puzzle;
    this->depth = 0;
    this->misplaced = this->depth + this->misplacedHeuristic();
    this->fn = this->depth + this->manhattanDistance();
	this->setRowCol();
}

// MISPLACED TILE HEURISTIC
int node::misplacedHeuristic() {
    int numMisplaced = 0;

    // Increment numMisplaced for each misplaced tile in puzzle
    for(int i = 0; i < 3; i++) {
   		for (int j = 0; j < 3; j++) {
		    if (puzzle[i][j] != node::solved[i][j]) {
			    numMisplaced++;
   			}
	    }
    }
    return numMisplaced;
}

// MANHATTAN DISTANCE HEURISTIC
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
					    if (puzzle[i][j] == solved[k][l])
   							distance += abs(i - k) + abs(j - l); //Distance horizontally + vertically
    				}
	    		}
   			}
	    }
    }
    return distance;
}

// FIND ROW & COL OF EMPTY TILE (0)
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

// CHECK IF GOAL STATE
bool node::isGoalState() {
	if (puzzle == solved) {
    	return true;
	} else {
	    return false;
	}
}

// CHECK IF EMPTY PUZZLE
bool node::isEmptyPuzzle() {
	if (puzzle == emptyPuzzle) {
		return true;
	} else {
		return false;
	}
}

// OPERATORS (MOVE EMPTY TILE)
// UP
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

// DOWN
vector<vector<int>> node::down() {
	vector<vector<int>> newPuzzle = puzzle;
	if (row < int(newPuzzle.size()) - 1) {
		newPuzzle[row][col] = newPuzzle[row + 1][col];
		newPuzzle[row + 1][col] = 0;
	} else {
		return emptyPuzzle;
	}
	return newPuzzle;
}

// LEFT
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

// RIGHT
vector<vector<int>> node::right() {
	vector<vector<int>> newPuzzle = puzzle;
	if (col < int(newPuzzle[0].size()) - 1) {
		newPuzzle[row][col] = newPuzzle[row][col + 1];
		newPuzzle[row][col + 1] = 0;
	} else {
		return emptyPuzzle;
	}
	return newPuzzle;
}

// ACCESSORS
vector<vector<int>> node::getPuzzle() {return puzzle;}
int node::getDepth() {return depth;}
int node::getMisplaced() {return misplaced;}
int node::getFn() {return fn;}
int node::getRow() {return row;}
int node::getCol() {return col;}
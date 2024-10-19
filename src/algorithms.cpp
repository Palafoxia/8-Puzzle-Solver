#include "algorithms.h"
#include "node.h"

#include <iostream>
#include <algorithm>
#include <cmath>

// Vector of visited puzzles
vector<vector<vector<int>>> visitedPuzzles;

// Search tree
queue<node> tree;

// Unordered map of parents for trace back
unordered_map<int, vector<vector<int>>> trace;

// UNIFORM COST SEARCH (BREADTH-FIRST SEARCH)
void uniformCostSearch(vector<vector<int>> puzzle) {	
	// Puzzle is not solvable
	if(!isSolvable(puzzle)) {cout << "Puzzle is not solvable!" << endl; return;}

	// Initialize search tree with root node
	tree = setupSearch(puzzle);

	// Loop until goal state is reached
	int depth = 0;
	while (true) {
        // Get node from front of queue
		node currentNode = tree.front();

		// Initialize
		vector<vector<int>> currentPuzzle = currentNode.getPuzzle();
		int row = currentNode.getRow();
		int col = currentNode.getCol();

		// PERFORM OPERATORS ON UNVISITED PUZZLES
		// Mark new puzzles as visited
		// Add new puzzles to trace map
		// Push new nodes to search tree
		// Break out of loop if operator results in goal state
		up(currentPuzzle, row, col, currentNode);
		if(tree.back().isGoalState()) {depth = tree.back().getDepth(); break;}
		down(currentPuzzle, row, col, currentNode);
		if(tree.back().isGoalState()) {depth = tree.back().getDepth(); break;}
		left(currentPuzzle, row, col, currentNode);
		if(tree.back().isGoalState()) {depth = tree.back().getDepth(); break;}
		right(currentPuzzle, row, col, currentNode);
		if(tree.back().isGoalState()) {depth = tree.back().getDepth(); break;}

		// Pop currentNode
		tree.pop();
	}

	// Print depth and expanded nodes information
	cout << "Solution found at depth " << depth << endl;
	cout << "Total expanded nodes: " << visitedPuzzles.size() << endl;

	// Print steps to solve puzzle
	printTrace(depth);
}

// A-STAR SEARCH
void AStarSearch(vector<vector<int>> puzzle, string heuristic) { // Manhattan or misplaced heuristic
	// Puzzle is not solvable
	if(!isSolvable(puzzle)) {cout << "Puzzle is not solvable!" << endl; return;}

	// Initialize search tree with root node
	tree = setupSearch(puzzle);

	// Frontier Vector Initialization
	vector<node> frontier {tree.front()};

	// Change heuristic string to lowercase
	transform(heuristic.begin(), heuristic.end(), heuristic.begin(), ::tolower);

	// Loop until goal state is reached
	int depth = 0;
	while (true) {
		// Get node from front of frontier
		node currentNode = frontier.front();

		// Initialize
		vector<vector<int>> currentPuzzle = currentNode.getPuzzle();
		int row = currentNode.getRow();
		int col = currentNode.getCol();

		// PERFORM OPERATORS ON UNVISITED PUZZLES
		// Mark new puzzles as visited
		// Add new puzzles to trace map
		// Push new nodes to search tree
		// Break out of loop if operator results in goal state
		up(currentPuzzle, row, col, currentNode);
		if(tree.back().isGoalState()) {depth = tree.back().getDepth(); break;}
		down(currentPuzzle, row, col, currentNode);
		if(tree.back().isGoalState()) {depth = tree.back().getDepth(); break;}
		left(currentPuzzle, row, col, currentNode);
		if(tree.back().isGoalState()) {depth = tree.back().getDepth(); break;}
		right(currentPuzzle, row, col, currentNode);
		if(tree.back().isGoalState()) {depth = tree.back().getDepth(); break;}

		// Pop the expanded node from frontier
		frontier.erase(frontier.begin());

		// Push the new nodes to the frontier and empty the tree
		while(!tree.empty()) {
			frontier.push_back(tree.front());
			tree.pop();
		}

		// Sort frontier in increasing order of either fn (Manhattan Distance) or misplaced value
		if(heuristic == "manhattan") {
			sort(frontier.begin(), frontier.end(), [](const node& x, const node& y) {
				return x.getFn() < y.getFn(); 
			});
		} else if (heuristic == "misplaced") {
			sort(frontier.begin(), frontier.end(), [](node x, node y) {
				return x.getMisplaced() < y.getMisplaced(); 
			});
		}
	}

	// Print depth and expanded nodes information
	cout << "Solution found at depth " << depth << endl;
	cout << "Total expanded nodes: " << visitedPuzzles.size() << endl;

	// Print steps to solve puzzle
	printTrace(depth);
}

// UP
void up(vector<vector<int>> newPuzzle, int row, int col, node currentNode) {
	if (row > 0) {
			newPuzzle[row][col] = newPuzzle[row - 1][col];
			newPuzzle[row - 1][col] = 0;
			// Push puzzle to tree if not already visited
			pushPuzzle(newPuzzle, currentNode);
		}
}

// DOWN
void down(vector<vector<int>> newPuzzle, int row, int col, node currentNode) {
	if(row < int(newPuzzle.size()) - 1) {
			newPuzzle[row][col] = newPuzzle[row + 1][col];
			newPuzzle[row + 1][col] = 0;
			// Push puzzle to tree if not already visited
			pushPuzzle(newPuzzle, currentNode);
		}
}

// LEFT
void left(vector<vector<int>> newPuzzle, int row, int col, node currentNode) {
	if(col > 0) {
			newPuzzle[row][col] = newPuzzle[row][col - 1];
			newPuzzle[row][col - 1] = 0;
			// Push puzzle to tree if not already visited
			pushPuzzle(newPuzzle, currentNode);
		}
}

// RIGHT
void right(vector<vector<int>> newPuzzle, int row, int col, node currentNode) {
	if(col < int(newPuzzle[0].size()) - 1) {
			newPuzzle[row][col] = newPuzzle[row][col + 1];
			newPuzzle[row][col + 1] = 0;
			// Push puzzle to tree if not already visited
			pushPuzzle(newPuzzle, currentNode);
		}
}

// Initialize root node and clear visited puzzles / trace map
queue<node> setupSearch(vector<vector<int>> p) {
	// Reset visited puzzles & trace map
    visitedPuzzles.clear();
	trace.clear();

	// Make queue and create root with initial state
	node root = node(p);
	queue<node> t;
	t.push(root);

	return t;
}

// Push valid puzzle to search tree
void pushPuzzle(vector<vector<int>> p, node n) {
	if(!isVisitedPuzzle(p)) {
		visitedPuzzles.push_back(p); // Mark puzzle as visited
		trace[hashPuzzle(p)] = n.getPuzzle(); // Add puzzle to trace map

		// Create new node and push to tree
		node newNode = node(p, n.getDepth());
		tree.push(newNode);
	}
}

// Flatten 2D vector to 1D
vector<int> flatten(vector<vector<int>> p) {
	vector<int> p1D;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            p1D.push_back(p[i][j]);
        }
    }
	return p1D;
} 

// Hash each puzzle to give a unique identifier
int hashPuzzle(vector<vector<int>> p) {
	// Flatten puzzle to 1D
    vector<int> puzzle1D = flatten(p);

	// Apply hash function
	int hash = 0;
	for(int i = 0; i < int(puzzle1D.size()); i++) {
		hash += puzzle1D[i] * pow(10, i);
	}
	return hash;
}

// Check if puzzle is solvable
bool isSolvable(vector<vector<int>> p) {
    // Flatten puzzle to 1D
    vector<int> puzzle1D = flatten(p);

    // Count inversions and determine if solvable
    int inversions = 0;
    for (int i = 0; i < 9 - 1; i++) {
        for (int j = i + 1; j < 9; j++) {
            if(puzzle1D[j] && puzzle1D[i] && puzzle1D[i] < puzzle1D[j]) {
                inversions++;
            }
        }
    }
    return (inversions % 2 == 0);
}

// Check if puzzle has been visited
bool isVisitedPuzzle(vector<vector<int>> p) {
	for (int i = 0; i < int(visitedPuzzles.size()); i++) {
		if (p == visitedPuzzles[i]) {
			return true;
		}
	}
	return false;
}

// Determine what move was done given 2 puzzles
string moveChoice(vector<vector<int>> p1, vector<vector<int>> p2) {
	// Flatten both puzzles to 1D
	vector<int> p11D = flatten(p1);
	vector<int> p21D = flatten(p2);

	// Find the 0 index in both puzzles
	int zero1, zero2;
	for(int i = 0; i < 9; i++) {
		if(p11D[i] == 0) zero1 = i;
		if(p21D[i] == 0) zero2 = i;
	}

	// Determine what move was done
	if(zero1 - zero2 == 3) return "UP";
	else if(zero1 - zero2 == -3) return "DOWN";
	else if(zero1 - zero2 == 1) return "LEFT";
	else return "RIGHT";
}

// Print puzzle
void printPuzzle(vector<vector<int>> p) {
	for (int i = 0; i < int(p.size()); i++) {
		cout << "| ";
		for (int j = 0; j < int(p[i].size()); j++) {
			cout << p[i][j] << " ";
		}
		cout << "|" << endl;
	}
	cout << endl;
}

// Create traceList and print all steps to solve puzzle
void printTrace(int depth) {
	// Ask user if they want to see the steps
	string choice;

	while (true) {
		cout << "\nWould you like to see the steps to solve the puzzle? (y/n)" << endl;
		cin >> choice;
		transform(choice.begin(), choice.end(), choice.begin(), ::tolower); // Transform choice to lowercase

		if(choice == "y") {
			// Initialize traceList with solved puzzle
			vector<vector<vector<int>>> traceList;
			vector<vector<int>> p = node::solved;
			traceList.insert(traceList.begin(), p);

			// Add each step to traceList
			for(int i = 0; i < depth; i++) {
				p = trace[hashPuzzle(p)];
				traceList.insert(traceList.begin(), p);
			}

			// Print Steps
			string move;
			for(int k = 0; k < depth + 1; k++){
				if(k == 0) {
					cout << "\nInitial Puzzle:" << endl;
				} else {
					cout << "Step " << k;
					cout << " (" << moveChoice(traceList[k - 1], traceList[k]) << "):" << endl;
				}
				printPuzzle(traceList[k]);
			}
			cout << "SOLVED!" << endl;
			cin.get();
			return;
		} else if(choice == "n") {
			cin.get();
			return;
		} else {
			cout << "\nPlease select y or n" << endl;
		}
	}
}
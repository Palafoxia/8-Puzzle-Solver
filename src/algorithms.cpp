#include "algorithms.h"
#include "node.h"

#include <iostream>
#include <algorithm>

// Global Variables
vector<vector<vector<int>>> visitedPuzzles; // Vector of visited puzzles

// UNIFORM COST SEARCH (BREADTH-FIRST SEARCH)
void uniformCostSearch(vector<vector<int>> puzzle) {
	// Setup search and create queue
	queue<node> tree = setupSearch(puzzle);
	if (tree.empty()) return; // Initial state is goal state

	// While loop until goal state is reached
	while (true) {
        // Get node from front of queue
		node currentNode = tree.front();

		// Not solvable
		if (tree.empty()) {
			cout << "No solution" << endl;
			return;
		}

        // Execute each operator (up, down, left, right) and push node to queue if necessary
        // Breaks out of while loop if node is goal state
        if(move(currentNode, currentNode.up(), tree)) {return;}
        if(move(currentNode, currentNode.down(), tree)) {return;}
        if(move(currentNode, currentNode.left(), tree)) {return;}
        if(move(currentNode, currentNode.right(), tree)) {return;}

		tree.pop();
	}
}

// A-STAR SEARCH
void AStarSearch(vector<vector<int>> puzzle, string heuristic) { // Manhattan or misplaced heuristic
	// Setup search and create queue
	queue<node> newNodes = setupSearch(puzzle);
	if (newNodes.empty()) return; // Initial state is goal state

	// Frontier Vector Initialization
	vector<node> frontier {newNodes.front()};

	// Change heuristic to lowercase
	transform(heuristic.begin(), heuristic.end(), heuristic.begin(), ::tolower);

	// While Loop
	while (true) {
		node currentNode = frontier.front();

		// Failure
		if (frontier.empty()) {
			cout << "No solution" << endl;
			return;
		}

		// Execute each operator (up, down, left, right) and push node to queue if necessary
        // Breaks out of while loop if node is goal state
        if(move(currentNode, currentNode.up(), newNodes)) {return;}
        if(move(currentNode, currentNode.down(), newNodes)) {return;}
        if(move(currentNode, currentNode.left(), newNodes)) {return;}
        if(move(currentNode, currentNode.right(), newNodes)) {return;}

		// Pop the expanded node
		frontier.erase(frontier.begin());

		// Add the new nodes to the back of the frontier and empty the newNodes tree
		while(!newNodes.empty()) {
			frontier.push_back(newNodes.front());
			newNodes.pop();
		}

		// Sort frontier in increasing order of either fn (Manhattan Distance) or misplaced value
		if(heuristic == "manhattan") {
			sort(frontier.begin(), frontier.end(), [](node x, node y) {
				return x.getFn() < y.getFn(); 
			});
		} else if (heuristic == "misplaced") {
			sort(frontier.begin(), frontier.end(), [](node x, node y) {
				return x.getMisplaced() < y.getMisplaced(); 
			});
		}
	}
}

// Setup Search
queue<node> setupSearch(vector<vector<int>> puzzle) {
	// Reset global variables
    visitedPuzzles.clear();

	// Make queue and create root with initial state
	node initialState = node(puzzle, -1);
	queue<node> tree;

	// Goal State is Initial State
	if (initialState.isGoalState()) {
		cout << "Solution found at depth " << initialState.getDepth() << endl;
		cout << "Total expanded nodes: " << visitedPuzzles.size() << endl;
		return tree;
	}
	tree.push(initialState);
	return tree;
}

// Execute move and push to queue
bool move(node currentNode, vector<vector<int>> move, queue<node>& tree) {
    if(move != node::emptyPuzzle && !isVisitedPuzzle(visitedPuzzles, move)) {
        node newNode = node(move, currentNode.getDepth()); // Create new node

        tree.push(newNode); // Push node to back of the queue
        visitedPuzzles.push_back(newNode.getPuzzle()); // Mark puzzle as visited;

        // Goal state reached
        if(newNode.isGoalState()) {
            cout << "Solution found at depth " << newNode.getDepth() << endl;
			cout << "Total expanded nodes: " << visitedPuzzles.size() << endl;
	        return true;
        }
    }
    return false;
}

// Check if puzzle has been visited
bool isVisitedPuzzle(vector<vector<vector<int>>> visitedPuzzles, vector<vector<int>> puzzle) {
	for (int i = 0; i < visitedPuzzles.size(); i++) {
		if (puzzle == visitedPuzzles[i]) {
			return true;
		}
	}
	return false;
}
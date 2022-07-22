// Project 1: The Eight-Puzzle

#include "algorithms.h"
#include "node.h"

#include <iostream>

int main() {
    vector<vector<int>> puzzle;
    int depth;
    bool run = true;

    // Prompt the user to choose a puzzle to solve
    cout << "Which puzzle would you like to solve?" << endl;

    while(run) {
        cout << "Options: 0, 2, 4, 8, 12, 16, 20, 24" << endl;
        cin >> depth;
        switch(depth) {
            case 0: puzzle = node::solved; run = false; break;
            case 2: puzzle = node::puzzle2; run = false; break;
            case 4: puzzle = node::puzzle4; run = false; break;
            case 8: puzzle = node::puzzle8; run = false; break;
            case 12: puzzle = node::puzzle12; run = false; break;
            case 16: puzzle = node::puzzle16; run = false; break;
            case 20: puzzle = node::puzzle20; run = false; break;
            case 24: puzzle = node::puzzle24; run = false; break;
            default: cout << "Invalid Option" << endl; break;
        }
    }

    // Run the search algorithms on the chosen puzzle
    if(depth < 16) {
        cout << endl << "UNIFORM COST SEARCH" << endl;
        uniformCostSearch(puzzle);
    } else {
        cout << endl << "Depth too high for uniform cost search (>=16)" << endl;
    }
    
    if(depth < 24) {
        cout << endl << "A* Misplaced SEARCH" << endl;
        AStarSearch(puzzle, "misplaced");
    } else {
        cout << endl << "Depth too high for A* Misplaced Search (>=24)" << endl;
    }

    cout << endl << "A* MANHATTAN SEARCH" << endl;
    AStarSearch(puzzle, "manhattan");

    cin.ignore(2);
}
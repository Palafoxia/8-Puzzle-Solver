// The Eight-Puzzle Solver
// Latest Update: 09/30/2024

// https://github.com/Palafoxia/8-Puzzle-Solver

#include "algorithms.h"
#include "node.h"
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Example 8-puzzles depth 2-24
vector<vector<int>> p2 {{1, 2, 3},{4, 5, 6},{0, 7, 8}};
vector<vector<int>> p4 {{1, 2, 3},{5, 0, 6},{4, 7, 8}};
vector<vector<int>> p8 {{1, 3, 6},{5, 0, 2},{4, 7, 8}};
vector<vector<int>> p12 {{1, 3, 6},{5, 0, 7},{4, 8, 2}};
vector<vector<int>> p16 {{1, 6, 7},{5, 0, 3},{4, 8, 2}};
vector<vector<int>> p20 {{7, 1, 2},{4, 8, 5},{6, 3, 0}};
vector<vector<int>> p24 {{0, 7, 2},{4, 6, 1},{3, 5, 8}};
vector<vector<vector<int>>> examplePuzzles = {p2, p4, p8, p12, p16, p20, p24};

// Algorithm list
vector<string> algorithms = {"Uniform Cost Search", "A* Search (Misplaced Heuristic)", "A* Search (Manhattan Heuristic)"};

// Print puzzle
void printPuzzle(vector<vector<int>> puzzle) {
	for (int i = 0; i < int(puzzle.size()); i++) {
		cout << "| ";
		for (int j = 0; j < int(puzzle[i].size()); j++) {
			cout << puzzle[i][j] << " ";
		}
		cout << "|" << endl;
	}
	cout << endl;
}

// Check if puzzle is solvable
bool isSolvable(vector<vector<int>> puzzle) {
    // Flatten puzzle to 1D
    vector<int> puzzle1D;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            puzzle1D.push_back(puzzle[i][j]);
        }
    }

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

// MAIN
int main() {
    vector<vector<int>> puzzle(3, vector<int>(3)); // 3 x 3 Puzzle to solve
    int depth, choice;
    bool run = true;
    vector<int> inputs;
    int num;

    // INTRODUCTION
    cout << "THE EIGHT-PUZZLE SOLVER" << endl;
    cout << "Implements optimal pathfinding search algorithms to solve 8-puzzles" << endl;
    cout << "----------------------------------------------------------------------" << endl;
    cout << "1. Solve an example puzzle" << endl;
    cout << "2. Build your own puzzle" << endl;
    cout << "3. Generate a random puzzle" << endl;
    cout << "4. Quit" << endl;
    
    cin >> choice;
    cout << endl;

    switch(choice) {

        //1. EXAMPLE PUZZLE
        case 1:
            // Choose which puzzle to solve
            for(int i = 0; i < 7; i++) {
                cout << "Depth ";
                if(i == 0) {cout << "2" << endl;}
                else {cout << i * 4 << endl;}
                printPuzzle(examplePuzzles[i]);
            }
            cout << "Which example puzzle would you like to solve?" << endl;
            cout << "Options: 2, 4, 8, 12, 16, 20, 24" << endl;

            while(true) {
                cin >> depth;
                if(depth == 2 || depth == 4 || depth == 8 || depth == 12 || depth == 16 || depth == 20 || depth == 24) {
                    cout << "\nSelected puzzle of solution depth " << depth << endl;
                    puzzle = examplePuzzles[depth/4];
                    break;
                } else { // Invalid input
                    cout << "\nPick a number from the options below" << endl;
                    cout << "Options: 2, 4, 8, 12, 16, 20, 24" << endl;
                    cin.clear();
                    cin.ignore(256, '\n');
                }
            }

            // Choose which algorithm to use
            run = true;
            while(run) {
                cout << "\nWhich algorithm would you like to use to solve the puzzle?" << endl;
                cout << "1. " << algorithms[0] << endl;
                cout << "2. " << algorithms[1] << endl;
                cout << "3. " << algorithms[2] << endl;
                cout << "4. All of the above" << endl;
        
                cin >> choice;
                switch(choice) {
                    case 1: // Uniform Cost Search
                        if(depth >= 16) { cout << "\nDepth too high for " << algorithms[0] << endl;}
                        else {
                            cout << "\nSolving puzzle of solution depth " << depth << " using " << algorithms[0] << "...." << endl;
                            uniformCostSearch(puzzle); run = false;
                        }
                        break;
                    case 2: // A-Star Search (Misplaced Heuristic)
                        if(depth >= 24) {cout << "\nDepth too high for " << algorithms[1] << endl;}
                        else {
                            cout << "\nSolving puzzle of solution depth " << depth << " using " << algorithms[1] << "...." << endl;
                            AStarSearch(puzzle, "misplaced"); run = false;
                        }
                        break;
                    case 3: // A-Star Search (Manhattan Heuristic)
                        cout << "\nSolving puzzle of solution depth " << depth << " using " << algorithms[1] << "...." << endl;
                        AStarSearch(puzzle, "manhattan"); run = false; break;
                    case 4: // All Algorithms
                        if(depth >= 24) {
                            cout << "\nDepth too high for " << algorithms[0] << " and " << algorithms[1] << endl;
                            cout << "\nSolving puzzle of solution depth " << depth << " using " << algorithms[2] << "...." << endl;
                            AStarSearch(puzzle, "manhattan");
                        } else if(depth >= 16) {
                            cout << "\nDepth too high for " << algorithms[0] << endl;
                            cout << "\nSolving puzzle of solution depth " << depth << " using " << algorithms[1] << "...." << endl;
                            AStarSearch(puzzle, "misplaced");
                            cout << "\nSolving puzzle of solution depth " << depth << " using " << algorithms[2] << "...." << endl;
                            AStarSearch(puzzle, "manhattan");
                        } else {
                            cout << "\nSolving puzzle of solution depth " << depth << " using all algorithms...." << endl;
                            cout << endl << algorithms[0] << endl;
                            uniformCostSearch(puzzle);
                            cout << endl << algorithms[1] << endl;
                            AStarSearch(puzzle, "misplaced");
                            cout << endl << algorithms[2] << endl;
                            AStarSearch(puzzle, "manhattan");
                        }
                        run = false; break;
                    default: // Invalid Input
                        cout << "\nInvalid Option" << endl;
                        cin.clear();
                        cin.ignore(256, '\n');
                        break;
                }       
            }
            break;

        // 2. BUILD YOUR OWN PUZZLE
        case 2:
            cout << "Build your puzzle by inputting numbers 0-8 (0 means empty)...." << endl;
            while(int(inputs.size()) < 9) {
                cin >> num;
                if(cin.fail()) { // Invalid input
                    cout << "Invalid option, input 0-8" << endl;
                    cin.clear();
                    cin.ignore(256, '\n');
                } else if(count(inputs.begin(), inputs.end(), num) == 1) { // Repeated number
                    cout << "You've already inputted " << num << endl;
                    cin.clear();
                    cin.ignore(256, '\n');
                } else if(num >= 0 && num <= 8) { // Valid input
                    inputs.push_back(num);
                    // Print current puzzle being built
                    cout << endl;
                    for (int i = 0; i < int(inputs.size()); i++) {
                        if(i % 3 == 0) {cout << "| ";}
                        cout << inputs[i] << " ";
                        if((i + 1) % 3 == 0) {cout << "|" << endl;}
                    }
                } else { // Invalid input
                    cout << "Invalid option, input 0-8" << endl;
                    cin.clear();
                    cin.ignore(256, '\n');
                }
            }
            
            // Set puzzle to inputs vector
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    puzzle[i][j] = inputs[(3 * i) + j];
                }
            }
            inputs.clear();

            // Check if solvable and solve
            if(!isSolvable(puzzle)) {
                cout << "Your puzzle is not solvable!" << endl;
                printPuzzle(puzzle);
            } else {
                cout << "Your puzzle is solvable!" << endl;
                printPuzzle(puzzle);
                cout << "Solving your puzzle using " << algorithms[2] << "...." << endl;
                AStarSearch(puzzle, "manhattan");
            }
            break;

        // 3. GENERATE RANDOM PUZZLE
        case 3:
            // Set puzzle to random nums from 0-8
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    // Set seed and random num
                    srand(time(0));
                    int random = rand() % 9;
                    // Don't repeat numbers
                    while(count(inputs.begin(), inputs.end(), random) == 1) {
                        random = rand() % 9;
                    }
                    inputs.push_back(random);
                    puzzle[i][j] = random;
                }
            }

            // Check if solvable and solve
            if(!isSolvable(puzzle)) {
                cout << "Your puzzle is not solvable!" << endl;
                printPuzzle(puzzle);
            } else {
                cout << "Your puzzle is solvable!" << endl;
                printPuzzle(puzzle);
                cout << "Solving your puzzle using " << algorithms[2] << "...." << endl;
                AStarSearch(puzzle, "manhattan");
            }
            break;

        // 4. QUIT
        case 4: cout << "Exiting program...." << endl; break;

        // INVALID CHOICE
        default: cout << "Please select a number from 1-4" << endl; break;

    }
    cin.ignore(256, '\n');
}
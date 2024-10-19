#pragma once

#include "node.h"

#include <queue>
#include <string>

// SEARCHES
void uniformCostSearch(vector<vector<int>>);
void AStarSearch(vector<vector<int>>, string);

//OPERATORS
void up(vector<vector<int>>, int, int, node);
void down(vector<vector<int>>, int, int, node);
void left(vector<vector<int>>, int, int, node);
void right(vector<vector<int>>, int, int, node);

// HELPER FUNCTIONS
queue<node> setupSearch(vector<vector<int>>);
void pushPuzzle(vector<vector<int>>, node);
vector<int> flatten(vector<vector<int>>);
int hashPuzzle(vector<vector<int>>);
bool isSolvable(vector<vector<int>>);
bool isVisitedPuzzle(vector<vector<int>>);
string moveChoice(vector<vector<int>>, vector<vector<int>>);
void printPuzzle(vector<vector<int>>);
void printTrace(int);
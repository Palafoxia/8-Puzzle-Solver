#pragma once

#include "node.h"

#include <queue>
#include <string>

// SEARCHES
void uniformCostSearch(vector<vector<int>>);
void AStarSearch(vector<vector<int>>, string);

// HELPER FUNCTIONS
queue<node> setupSearch(vector<vector<int>>);
bool move(node, vector<vector<int>>, queue<node>&);
bool isVisitedPuzzle(vector<vector<vector<int>>>, vector<vector<int>>);
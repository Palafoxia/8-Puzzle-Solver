#pragma once

#include "node.h"

#include <queue>
#include <string>

// Searches
void uniformCostSearch(vector<vector<int>>);
void AStarSearch(vector<vector<int>>, string);

// Helper Functions
queue<node> setupSearch(vector<vector<int>>);
bool isVisitedPuzzle(vector<vector<vector<int>>>, vector<vector<int>>);
bool move(node, vector<vector<int>>, queue<node>&);
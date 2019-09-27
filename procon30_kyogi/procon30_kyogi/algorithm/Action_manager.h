#pragma once
#include"../general.h"
#include"Prefetching.h"
#include"../Data/Agents.h"
#include"../Data/AgentsAction.h"
#include"../Data/AgentsEvalution.h"
#include"../Data/Field.h"
#include"../Data/Map.h"

class Action_manager {
public:
	int Action(int);
	vector<vector<int>>Now_Optim;


};
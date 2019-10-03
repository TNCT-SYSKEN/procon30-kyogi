#pragma once
#include"../general.h"
#include"Prefetching.h"
#include"../Data/Agents.h"
#include"../Data/AgentsAction.h"
#include"../Data/AgentsEvalution.h"
#include"../Data/Field.h"
#include"../Data/Map.h"
#include"Judge.h"

class Action_manager {
public:
	void Action();
	vector<vector<int>>Now_Optim;


};
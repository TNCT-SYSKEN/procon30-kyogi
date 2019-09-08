#pragma once
#include"../general.h"
#include"Field_test.h"
#include"../Data/Field.h"
#include"../Data/Agents.h"
#include"../Data/AgentsAction.h"
#include"../Data/Map.h"
#include"../Data/AgentsEvalution.h"


class ActionManager {
public:
	void Action(int);

	vector<vector<int>>Now_Optim;


};
#pragma once
#include "CreateMap.h"
#include"../general.h"
#include"../json/FetchJson.h"
#include"../Data/Agents.h"
#include"../Data/AgentsAction.h"
#include"../Data/Field.h"



class InputOutputManager
{
public:
	//jsonなかったら無限ループ
	void init();
	void inputOutputManager();
};


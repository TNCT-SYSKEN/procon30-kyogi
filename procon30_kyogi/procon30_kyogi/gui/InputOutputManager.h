#pragma once
#include "CreateMap.h"
#include"../general.h"
#include"../json/FetchJson.h"
#include"../Data/Agents.h"


class InputOutputManager
{
public:
	//jsonなかったら無限ループ
	void init();
	void inputOutputManager();
};


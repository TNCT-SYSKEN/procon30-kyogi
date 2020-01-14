#pragma once
#include"../gui/InputOutputManager.h"

class Initialize {
public:
	void initialize();

private:
	void setupMap();
	void setupField();
	void setupAgents();
	void setupAgentsAction();
};
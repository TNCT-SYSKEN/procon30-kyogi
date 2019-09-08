#include "Agents.h"
Agents* Agents::AllAgents = nullptr;


Agents* Agents::getAgents() {	
	return AllAgents;
}


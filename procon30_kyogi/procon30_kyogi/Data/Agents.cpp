#include "Agents.h"
Agents* Agents::AllAgents = nullptr;


Agents* Agents::getAgents() {	
	if (AllAgents == nullptr) {
		AllAgents = new Agents;
	}
	return AllAgents;
}


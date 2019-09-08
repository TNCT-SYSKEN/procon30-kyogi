#include"AgentsAction.h"
AgentsAction* AgentsAction::agentsAction = nullptr;

AgentsAction* AgentsAction::getAgentsAction() {
	if (agentsAction == nullptr) {
		agentsAction = new AgentsAction;
	}
	return agentsAction;
}
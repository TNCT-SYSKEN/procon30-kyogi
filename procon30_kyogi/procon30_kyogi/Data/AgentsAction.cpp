#include"AgentsAction.h"
AgentsAction* AgentsAction::agentsAction = nullptr;

AgentsAction* AgentsAction::getAgentsAction() {

	return agentsAction;
}
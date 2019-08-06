#include"AgentsEvalution.h"
AgentsEvalution* agentsEvalution = nullptr;
AgentsEvalution * AgentsEvalution::getAgentsEvalution()
{
	if (agentsEvalution == nullptr) {
		agentsEvalution = new AgentsEvalution;
	}
	return agentsEvalution;
}

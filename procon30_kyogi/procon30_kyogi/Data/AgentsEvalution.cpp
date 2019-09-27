#include"AgentsEvalution.h"
AgentsEvalution* AgentsEvalution::gentsEvalution = nullptr;
AgentsEvalution* AgentsEvalution::getAgentsEvalution()
{
	if (gentsEvalution == nullptr) {
		gentsEvalution = new AgentsEvalution;
	}
	return gentsEvalution;
}
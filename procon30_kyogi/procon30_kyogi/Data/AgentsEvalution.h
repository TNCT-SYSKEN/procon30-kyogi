#pragma once
#include"../general.h"
class AgentsEvalution {
public:

	/*************** new ver*************/

	
	//�ō��]���_���[�g
	//{ (agentnum1) {(turn 1){agentnum1,{dx,dy}}, (turn 2){agentnum1,{dx,dy}},...} , (agentnum 2){(turn1)}}
	vector<vector<pair<int, int>>>maxRoute;
	float maxEvalutionPoint;

	// �]���_�v�Z�̎��̃^�[����ǂ݃^�C����
	vector<vector<int>> turnTiledField;


	/************* judge *******************/


	static AgentsEvalution* getAgentsEvalution();

private:
	static AgentsEvalution* gentsEvalution;
};
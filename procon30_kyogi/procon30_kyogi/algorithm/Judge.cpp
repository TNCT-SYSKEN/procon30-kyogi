#include"Judge.h"


//�S�ẴG�[�W�F���g�ɂ��Ĉ�C�ɕ]���_�v�Z�������ق���
//�ꏊ�ύX�Ȃǂ����₷��

//�]���_�v�Z�ɕK�v�ȏ���
//�t�B�[���h���A�^�C���󋵁A�G�[�W�F���g�̈ʒu
//�����̃`�[���̓��_�A����̃`�[���̓��_
//���ꂼ��������Ƃ��Ĉ���




//�S�T�����[�h
void Judge::fullSearch() {

	int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
	int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };

	Map* map;
	map = map->getMap();
	Agents* agents;
	agents = agents->getAgents();
	AgentsEvalution* agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();
	AgentsAction* agentsAction;
	agentsAction = agentsAction->getAgentsAction();


	//�G���[�g
	vector<pair<int,pair<int,int>>>enemyRoute = {};
	int ourAgentsS = agents->ourAgents.size();

	pair<int,int>agentsPosition;
	for (int agentsnum = agents->otherAgents[0][0]; agentsnum < agents->otherAgents[0][0]; agentsnum++) {
		//agents[0][1]�ȂǂɃA�N�Z�X
		agentsPosition.first = agents->otherAgents[agentsnum - agents->otherAgents[0][0]][1] - 1;
		agentsPosition.second = agents->otherAgents[agentsnum - agents->otherAgents[0][0]][2] - 1;

		enemyRoute.push_back(make_pair(agentsnum, agentsPosition));
		//�G�œK���[�g������
		//	�����Ő�ǂ݃^�[�����ɉ������T�C�Y������������
		agentsEvalution->enemyMaxRoute.resize(0);
		agentsPosition=

	}



}

void Judge::calculateTilePoint(vector<pair<int, pair<int, int>>>route,int teamID) {
	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();
	
	int sum = 0;



	//�c��̃^�[���������v�Z
	rep(counter,map->finalTurn - map->turn+1)
		rep(i, map->width) {
			rep(j, map->vertical) {
				if()
				
			}
		}

}



void Judge::calculateAreaPoint(vector<pair<int,pair<int,int>>>route,int teamID,int sum) {
	



}


void Judge::calculateEnemyEvalution(vector<pair<int, pair<int, int>>>route, int sum) {

}



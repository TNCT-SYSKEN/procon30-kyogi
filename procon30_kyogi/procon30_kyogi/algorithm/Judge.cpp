#include"Judge.h"


//�S�ẴG�[�W�F���g�ɂ��Ĉ�C�ɕ]���_�v�Z�������ق���
//�ꏊ�ύX�Ȃǂ����₷��

//�]���_�v�Z�ɕK�v�ȏ���
//�t�B�[���h���A�^�C���󋵁A�G�[�W�F���g�̈ʒu
//�����̃`�[���̓��_�A����̃`�[���̓��_
//���ꂼ��������Ƃ��Ĉ���



//����
//���񂾌�̃^�C����������x��邩������Ȃ�
//


//�S�T�����[�h
void Judge::fullSearch() {


	Map* map;
	map = map->getMap();
	Agents* agents;
	agents = agents->getAgents();
	AgentsEvalution* agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();
	AgentsAction* agentsAction;
	agentsAction = agentsAction->getAgentsAction();


	//�G���[�g
	vector<pair<int,pair<int,int>>>enemyRoute(1);
	int ourAgentsS = agents->ourAgents.size();

	//�^�C�����������}�X�̍��W�A��ǂ݃^�[�����̋L�^
	vector<pair<int, pair<int, int>>>moveUpTile;

	pair<int,int>agentsPosition;
	for (int agentsnum = agents->otherAgents[0][0]; agentsnum < agents->otherAgents[0][0]; agentsnum++) {
		//agents[0][1]�ȂǂɃA�N�Z�X
		agentsPosition.first = agents->otherAgents[agentsnum - agents->otherAgents[0][0]][1] - 1;
		agentsPosition.second = agents->otherAgents[agentsnum - agents->otherAgents[0][0]][2] - 1;

		enemyRoute.push_back(make_pair(agentsnum, agentsPosition));
		//�G�œK���[�g������
		
		/*	�����Ő�ǂ݃^�[�����ɉ������T�C�Y������������	*/
		agentsEvalution->maxRoute.resize(map->finalTurn - map->turn + 1);
		agentsEvalution->maxEvalutionPoint = 0;
		agentsEvalution->enemyMaxRoute.resize(0);
		agentsEvalution->enamyMaxEvalutionPoint = 0;
		

		


		
		//�s���\��
		calculateEnemyRoute(enemyRoute, agentsPosition,moveUpTile ,0,map->finalTurn-map->turn+1, 0);






	}



}

void Judge::calculateTilePoint(vector<pair<int, pair<int, int>>>route, int teamID) {
	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();

	int sum = 0;




}



void Judge::calculateAreaPoint(vector<pair<int,pair<int,int>>>route,int teamID,int sum) {
	



}


void Judge::calculateEnemyRoute(vector<pair<int, pair<int, int>>>route, pair<int, int> nowAgentPosition,
	vector<pair<int, pair<int, int>>>moveUpTile, int moveup, int readTurn, int sum) {
	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();


	int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
	int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };

	rep(turn, 9) {
		

		if (nowAgentPosition.first + dx[turn] < 0 || nowAgentPosition.first + dx[turn] >= map->width
			|| nowAgentPosition.second + dy[turn] < 0 || nowAgentPosition.second + dy[turn] >= map->vertical) {
			goto CantGoThere;
		}
		//���񂾂̂��G�i���g�j�̃^�C����������A�N�Z�X���Ȃ�
		if (field->tiled[nowAgentPosition.first + dx[turn]][nowAgentPosition.second + dy[turn]] == map->otherTeamID) {
			goto CantGoThere;
		}

		if (turn == 4) {

		}
		else {


			if (field->tiled[nowAgentPosition.first + dx[turn]][nowAgentPosition.second + dy[turn]] == map->ourTeamID) {
				//moveup��resize
				moveUpTile.resize(moveup + 1);
				moveUpTile[moveup] = make_pair(map->finalTurn - map->turn + 2 - readTurn,
					(nowAgentPosition.first + dx[turn], nowAgentPosition.second + dy[turn]));
				moveup++;
				
			}
			else {

				nowAgentPosition.first += dx[turn];
				nowAgentPosition.second += dy[turn];
			}	
		}
		//route�T�C�Y����
		route.resize(route.size()+1);
		route.push_back(make_pair(route[0].first, make_pair(dx[turn], dy[turn])));

		if (readTurn > 0) {
			readTurn--;
			calculateEnemyRoute(route, nowAgentPosition, moveUpTile, moveup, readTurn, sum);
		}
		else {
			JudgeEvalution judgeEvalution;
			judgeEvalution.calculateEnemyEvalution(route, moveUpTile, moveup, sum);
		}

	}



	CantGoThere:;
}



#include"Judge.h"


//�S�ẴG�[�W�F���g�ɂ��Ĉ�C�ɕ]���_�v�Z�������ق���
//�ꏊ�ύX�Ȃǂ����₷��


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
	Field* field;
	field = field->getField();



	//�G���[�g
	vector<pair<int,pair<int,int>>>enemyRoute(0);
	int ourAgentsS = agents->ourAgents.size();

	//�^�C�����������}�X�̍��W�A��ǂ݃^�[�����̋L�^
	vector<pair<int, pair<int, int>>>moveUpTile;

	//�G�̊l���ő�|�C���g�i���v�j
	int enemyGetPointMax = 0;

	agentsEvalution->enemyMaxRoute.resize(ourAgentsS,vector<pair<int,pair<int,int>>>(map->finalTurn-map->turn));
	agentsEvalution->enemyMaxGetPoint.resize(ourAgentsS, 0);


	pair<int,int>agentsPosition;
	for (int agentsnum = agents->otherAgents[0][0]; agentsnum < agents->otherAgents[0][0] +ourAgentsS; agentsnum++) {
		//agents[0][1]�ȂǂɃA�N�Z�X
		agentsPosition.first = agents->otherAgents[agentsnum - agents->otherAgents[0][0]][1] - 1;
		agentsPosition.second = agents->otherAgents[agentsnum - agents->otherAgents[0][0]][2] - 1;

		enemyRoute.push_back(make_pair(agentsnum, agentsPosition));
		//�G�œK���[�g������

		//	�����Ő�ǂ݃^�[�����ɉ������T�C�Y������������
		agentsEvalution->enemyMaxRoute.resize(0);
	
		
		//�s���\��
		calculateEnemyRoute(enemyRoute, agentsPosition,moveUpTile ,0,map->finalTurn-map->turn, 0);

		//�ő�_�𑊎�`�[�����l������
		enemyGetPointMax += agentsEvalution->enemyMaxGetPoint[agentsnum - agents->otherAgents[0][0]];
		enemyRoute.resize(0);
	}


	/* �������瑊��̍ő�_�𒴂���_���Ƃ�悤�ɐݒ肷�� */
	


	//���ׂ��_��
	//����̑����_�[�����̑����_ + ����̎�肤��ő�_
	int needGetPoint = map->score[1][0] - map->score[0][0] + enemyGetPointMax;


	/*	�����Ő�ǂ݃^�[�����ɉ������T�C�Y������������	*/
	agentsEvalution->ourMaxRoute.resize(agents->ourAgents.size(),vector<pair<int,pair<int,int>>>(map->finalTurn - map->turn));
	agentsEvalution->ourMaxGetPoint.resize(map->finalTurn-map->turn,0);

	vector<pair<int, pair<int, int>>> ourRoute;
	int ourGetPointMax = 0;

	//�����̃`�[���̍ő�_���߂��
	for (int agentsnum = agents->ourAgents[0][0]; agentsnum < agents->ourAgents[0][0] + ourAgentsS; agentsnum++) {

		agentsPosition.first = agents->ourAgents[agentsnum - agents->ourAgents[0][0]][1];
		agentsPosition.second = agents->ourAgents[agentsnum - agents->ourAgents[0][0]][2];

		ourRoute.push_back(make_pair(agentsnum,agentsPosition));

		calculateOurRoute(ourRoute, agentsPosition, moveUpTile, 0, map->finalTurn - map->turn, 0);
		//�ō��_���Z
		ourGetPointMax += agentsEvalution->ourMaxGetPoint[agentsnum - agents->ourAgents[0][0]];
		
		//�����
		ourRoute.resize(0);
	}


	//�������瑊��̓_������悤�������U�������肷��
	//���������邩��
	/*
	int fieldTiled[20][20];
	rep(i, map->width) {
		rep(j, map->vertical) {
			fieldTiled[i][j] = field->tiled[i][j];
		}
	}
	*/

}






void Judge::calculateEnemyRoute(vector<pair<int, pair<int, int>>>route, pair<int, int> nowAgentPosition,
	vector<pair<int, pair<int, int>>>moveUpTile, int moveup, int readTurn, int sum) {
	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();


	int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
	int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };

	bool moveCheck = false;

	int movedTiled[20][20];
	rep(i, map->width) {
		rep(j, map->vertical) {
			movedTiled[i][j] = field->tiled[i][j];
		}
	}

	rep(turn, 9) {
		

		if (nowAgentPosition.first + dx[turn] < 0 || nowAgentPosition.first + dx[turn] >= map->width
			|| nowAgentPosition.second + dy[turn] < 0 || nowAgentPosition.second + dy[turn] >= map->vertical) {
			goto CantGoThere;
		}
		//���񂾂̂��G�i���g�j�̃^�C����������A�N�Z�X���Ȃ�
		if (movedTiled[nowAgentPosition.first + dx[turn]][nowAgentPosition.second + dy[turn]] == map->otherTeamID) {
			if (turn == 4) {

			}
			else {

				goto CantGoThere;
			}
		}

		if (turn == 4) {


		}
		else {


			if (movedTiled[nowAgentPosition.first + dx[turn]][nowAgentPosition.second + dy[turn]] == map->ourTeamID) {
				//moveup��resize

				if (readTurn > 0) {
					moveUpTile.resize(moveup + 1);

					//1,2,3,4,5
					moveUpTile[moveup] = make_pair(map->finalTurn - map->turn + 1 - readTurn,
						make_pair(nowAgentPosition.first + dx[turn], nowAgentPosition.second + dy[turn]));
					moveup++;
					moveCheck = true;
					movedTiled[nowAgentPosition.first + dx[turn]][nowAgentPosition.second + dy[turn]];
				}
				
			}
			else {

				nowAgentPosition.first += dx[turn];
				nowAgentPosition.second += dy[turn];
			}	
		}
		//route�T�C�Y����
		

		if (readTurn > 0) {
			
			route.resize(route.size()+1);
			route.push_back(make_pair(route[0].first, make_pair(dx[turn], dy[turn])));
			readTurn--;
			calculateEnemyRoute(route, nowAgentPosition, moveUpTile, moveup, readTurn, sum);
		}
		else {
			JudgeEvalution judgeEvalution;
			judgeEvalution.calculateEnemyEvalution(route, moveUpTile, moveup, sum);

		}
	

		//�ЂƂO������
		route.resize(route.size() - 1);
	CantGoThere:;
	}



	
}


void Judge::calculateOurRoute(vector<pair<int, pair<int, int>>>route, pair<int, int> nowAgentPosition,
	vector<pair<int, pair<int, int>>>moveUpTile, int moveup, int readTurn, int sum) {

	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();

	int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
	int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };

	bool moveCheck = false;

	int movedTiled[20][20];
	rep(i, map->width) {
		rep(j, map->vertical) {
			movedTiled[i][j] = field->tiled[i][j];
		}
	}

	rep(turn, 9) {

		if (nowAgentPosition.first + dx[turn] < 0 || nowAgentPosition.first + dx[turn] >= map->width
			|| nowAgentPosition.second + dy[turn] < 0 || nowAgentPosition.second + dy[turn] >= map->vertical) {
			goto CantGoThere;
		}
		//���񂾂̂������`�[���̃^�C����������A�N�Z�X���Ȃ�
		if (movedTiled[nowAgentPosition.first + dx[turn]][nowAgentPosition.second + dy[turn]] == map->ourTeamID) {
			if (turn == 4) {

			}
			else {

				goto CantGoThere;
			}
		}

		if (turn == 4) {

		}
		else {


			if (movedTiled[nowAgentPosition.first + dx[turn]][nowAgentPosition.second + dy[turn]] == map->otherTeamID) {
				//moveup��resize

				if (readTurn > 0) {
					moveUpTile.resize(moveup + 1);

					//1,2,3,4,5
					moveUpTile[moveup] = make_pair(map->finalTurn - map->turn + 1 - readTurn,
						make_pair(nowAgentPosition.first + dx[turn], nowAgentPosition.second + dy[turn]));
					moveup++;
					moveCheck = true;
					movedTiled[nowAgentPosition.first + dx[turn]][nowAgentPosition.second + dy[turn]];
				}

			}
			else {

				nowAgentPosition.first += dx[turn];
				nowAgentPosition.second += dy[turn];
			}
		}
		//route�T�C�Y����


		if (readTurn > 0) {

			route.resize(route.size() + 1);
			route.push_back(make_pair(route[0].first, make_pair(dx[turn], dy[turn])));
			readTurn--;
			calculateOurRoute(route, nowAgentPosition, moveUpTile, moveup, readTurn, sum);
		}
		else {
			JudgeEvalution judgeEvalution;
			judgeEvalution.calculateEnemyEvalution(route, moveUpTile, moveup, sum);

		}


		//�ЂƂO������
		route.resize(route.size() - 1);
	CantGoThere:;
	}

}





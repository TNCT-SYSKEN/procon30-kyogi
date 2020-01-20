#include"Prefetching.h"
#include"Evalution.h"
#include"../Data/AgentsEvalution.h"


void Prefetching::hyoukaKeisan()
{
	int dx[9] = { 1,1,1,0,0,0,-1,-1,-1 };
	int dy[9] = { 1,0,-1,1,0,-1,1,0,-1 };

	Map *map;
	map = map->getMap();


	Agents* agents;
	agents = agents->getAgents();
	AgentsEvalution *agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();
	AgentsAction *agentsAction;
	agentsAction = agentsAction->getAgentsAction();

	Field* field;
	field = field->getField();
	pair<int, int>agentPosition;


	//agentnumber,<agentpositionX,Y>
	vector<pair<int, pair<int, int>>>route;//�o�H������
	int ourAgentsS = agents->ourAgents.size();


	//maxRoute,actionDXDY�̏�����
	agentsEvalution->maxRoute.resize(0);
	agentsEvalution->maxRoute.resize(agents->ourAgents.size(), vector<pair<int, pair<int, int>>>(0));
	

	agentsAction->actionType.resize(0);
	agentsAction->actionType.resize(ourAgentsS);

	// turn ���Ƃ̃^�C����
	vector<vector<vector<int>>> moveUpTile;
	moveUpTile.resize(map->readTurn, vector<vector<int>>(map->width, vector<int>(map->vertical)));
	rep(i, map->width) {
		rep(j, map->vertical) {
			moveUpTile[0][i][j] = field->tiled[i][j];
		}
	}


	//�G�[�W�F���g�̐��������[�v
	for (int agentsnum = 0; agentsnum < ourAgentsS; agentsnum++) {
		//
		agentPosition = make_pair((agents->ourAgents[agentsnum][1]), (agents->ourAgents[agentsnum][2]));//


			//agent�̏����ʒu
		route.push_back(make_pair(agents->ourAgents[agentsnum][0], agentPosition));

		//agentsEvalution��max�]���l��������
		agentsEvalution->maxEvalutionPoint = mINF;

		
		//���ԖڂɌv�Z
		calculateEvalution(route, agentPosition, moveUpTile, agentsnum, map->readTurn, 0);

		route.resize(0);


		/*�����܂Ō���*/
		/////////////////////////////////////////////////////////
		//AgentsAction.h�ɏ�������
		agentsAction->actionDxDy[agentsnum].resize(0);

		agentsEvalution->maxEvalutionPoint = mINF;

		//
		int nowX = agents->ourAgents[agentsnum][1];
		int nowY = agents->otherAgents[agentsnum][2];

		rep(i, map->readTurn) {
			// ���������Position
			nowX += agentsEvalution->maxRoute[agentsnum][i].second.first;
			nowY += agentsEvalution->maxRoute[agentsnum][i].second.second;

			agentsAction->actionDxDy[agentsnum].push_back(
				agentsEvalution->maxRoute[agentsnum][i]);
			if (agentsEvalution->maxRoute[agentsnum][i].second.first == 0 &&
				agentsEvalution->maxRoute[agentsnum][i].second.second == 0) {
				//stay
				agentsAction->actionType[agentsnum].push_back(0);

			}
			else if (field->tiled[nowX][nowY] == map->otherTeamID){
				//remove
				agentsAction->actionType[agentsnum].push_back(-1);
				// moveUpTile�ɍX�V
				// ��̃^�[���̃^�C���ɂ����f
				for (int tmp = i; i < map->readTurn; i++) {
					moveUpTile[tmp + 1][nowX][nowY] = 0;
				}
				
				nowX -= agentsEvalution->maxRoute[agentsnum][i].second.first;
				nowY -= agentsEvalution->maxRoute[agentsnum][i].second.second;
			}
			else {
				//move	
				// moveUpTile�ɍX�V
				// ��̃^�[���̃^�C���ɂ����f
				for (int tmp = i; i < map->readTurn; i++) {
					moveUpTile[tmp + 1][nowX][nowY] = map->ourTeamID;
				}
				agentsAction->actionType[agentsnum].push_back(1);

			}
		}
	}

}



//�o�H�v�Z
void  Prefetching::calculateEvalution(vector<pair<int, pair<int, int>>>route, pair<int, int> nowAgentPosition,
	vector<vector<vector<int>>>moveUpTile, int agentsnum, int readTurn, int sum)
{

	int dx[9] = { 1,1,1,0,0,0,-1,-1,-1 };
	int dy[9] = { 1,0,-1,1,0,-1,1,0,-1 };
	
	Map* map;
	map = map->getMap();
	Agents* agents;
	agents = agents->getAgents();
	Field* field;
	field = field->getField();
	Evalution evalution;

	int Dx = nowAgentPosition.first, Dy = nowAgentPosition.second;
	int giveReadTurn;

	rep(turn, 9) {
		Dx = nowAgentPosition.first;
		Dy = nowAgentPosition.second;


			//��ʊO
		if (Dx + dx[turn] < 0 || Dx + dx[turn] >= map->width || Dy + dy[turn] < 0 || Dy + dy[turn] >= map->vertical) {
			goto fini;
		}

		//�߂낤�Ƃ���Ƃ��̏��O
		//dx,dy�������Ă�Ƃ�

		//�ړ��悪�����`�[���i�߂���܂܂��j
		if (moveUpTile[map->readTurn-readTurn][Dx + dx[turn]][Dy + dy[turn]] == map->ourTeamID) {
			// sum �����炷����
		}
		//�ړ��悪����`�[���^�C����������
		else if (moveUpTile[map->readTurn-readTurn][Dx + dx[turn]][Dy + dy[turn]] == map->otherTeamID) {

			moveUpTile[map->readTurn-readTurn][Dx + dx[turn]][Dy + dy[turn]] = 0;
			Dx -= dx[turn];
			Dy -= dy[turn];

		}
		else {
			// tile	��h��	
			moveUpTile[map->readTurn-readTurn][Dx + dx[turn]][Dy + dy[turn]] = map->ourTeamID;

		}


		//�ʒu�X�V
		Dx += dx[turn];
		Dy += dy[turn];

		//��ǂ݃^�[����(readTurn)���ċA�ŌĂяo�����т�-1
		if (readTurn > 1) {
			route.push_back(make_pair(route[0].first, make_pair(dx[turn], dy[turn])));
			giveReadTurn = readTurn - 1;


			calculateEvalution(route, make_pair(Dx, Dy), moveUpTile, agentsnum, giveReadTurn, sum);
			route.resize(route.size() - 1);

		}
		else if (readTurn == 1) {
			route.push_back(make_pair(route[0].first, make_pair(dx[turn], dy[turn])));

			//�]���v�Z
			evalution.calculateEvalution(route, moveUpTile, agentsnum, sum);
			route.resize(route.size() - 1);
		}


		//route.resize(route.size() - 1);
		//routeSize�̂��߂ɃG�[�W�F���g�̈ʒu���͈͊O�ł�push���Ă���łȂ���null�Q�Ƃ��N��������A
		//push_back���ׂ�

	fini:;
	}

}


#include"Prefetching.h"
#include"Evalution.h"
#include"../Data/AgentsEvalution.h"

int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };
vector<vector<int>> Prefetching::hyoukaKeisan()
{
	Map *map;
	map = map->getMap();
	Agents* agents;
	agents = agents->getAgents();
	AgentsEvalution *agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();
	AgentsAction *agentsAction;
	agentsAction = agentsAction->getAgentsAction();

	pair<int, int>agentPosition;
	
	//agentnumber,<agentpositionX,Y>
	vector<pair<int, pair<int, int>>>route = {};//�o�H������
	int ourAgentsS = agents->ourAgents.size();
	 //�G�[�W�F���g�̐��������[�v
	for (int agentsnum = agents->ourAgents[0][0]; agentsnum < agents->ourAgents[0][0]+ourAgentsS;agentsnum++) {
		//position��-1
		//�������Ȃ���json�Ƃ�hogehoge������肵�Â炢
		agentPosition.first = agents->ourAgents[agentsnum-agents->ourAgents[0][0]][1]-1;//x
		agentPosition.second = agents->ourAgents[agentsnum-agents->ourAgents[0][0]][2]-1;//y
		//agent�̏����ʒu
		route.push_back(make_pair(agentsnum,agentPosition));
		

		//agentsEvalution maxRoute vector�̉��
		vector<pair<int, int>>().swap(agentsEvalution->maxRoute);

		//agentsEvalution��max�]���l��������
		agentsEvalution->maxEvalutionPoint = 0;
		agentPosition = calculateEvalution(route,agentsnum,agentPosition,map->readTurn,0);
		//
	
			//AgentsAction.h�ɏ�������
		agentsAction->actionDxDy[agentsnum - agents->ourAgents[0][0]].second.push_back(agentPosition);
		agentsAction->actionDxDy[agentsnum - agents->ourAgents[0][0]].first = agentsnum;
		
		if (agentPosition.first == 0 && agentPosition.second == 0) {
			agentsAction->actionType[agentsnum - agents->ourAgents[0][0]].push_back(0);
		}
		else {
			agentsAction->actionType[agentsnum - agents->ourAgents[0][0]].push_back(1);
		}

	}

	

	

	return vector<vector<int>>();
}


//point�v�Z
int Prefetching::calculateScore(pair<int,int>agentPosition)
{
	Map *map;
	map = map->getMap();
	Field *field;
	field = field->getField();

	int sum = 0;

	if (agentPosition.first < 0 || agentPosition.first >= map->width || agentPosition.second < 0 || agentPosition.second >= map->vertical) {
		return -1;
	}
	else {
		sum = field->points[agentPosition.first][agentPosition.second];
	}

	return sum;
}

//�o�H�v�Z
pair<int,int> Prefetching::calculateEvalution(vector<pair<int,pair<int,int>>>route,int agentnum,pair<int,int>agentPosition,int readTurn,int sum)
{		
	Map* map;
	map = map->getMap();
	
	rep(turn,9) {

		//�s���Ȃ������ɍs�����Ƃ����Ƃ��ɋ����I��������
		if (agentPosition.first + dx[turn] < 0 || agentPosition.first + dx[turn] >= map->width
			|| agentPosition.second + dy[turn] < 0 || agentPosition.second + dy[turn] >= map->vertical) {
			goto CantGoThere;
		}


		agentPosition.first += dx[turn];
		agentPosition.second += dy[turn];

		route.push_back(make_pair(agentnum, agentPosition));

		if (turn == 4) 
		{
		
		}//�ړ����Ȃ�
		else {
			sum += calculateScore(agentPosition);
		}
		if (readTurn > 0) {
			readTurn--;
			//�ċA
			calculateEvalution(route, agentnum,agentPosition,readTurn,sum);
		}
		else {
			//�}��(�]���v�Z)
			Evalution evalution;
			evalution.calculateEvalution(route,sum);


			//route vector�̉��
			vector<pair<int, pair<int, int>>>().swap(route);
		}
	}

	

	//�s���Ȃ������ɍs�����Ƃ����Ƃ��ɋ����I��������
CantGoThere:;
	pair<int, int>Retur = make_pair(route[1].second.first, route[1].second.second);
	return Retur;
}


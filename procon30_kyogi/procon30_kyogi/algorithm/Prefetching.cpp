#include"Prefetching.h"
#include"Evalution.h"


int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };
vector<vector<int>> Prefetching::hyoukaKeisan()
{
	Map *map;
	map = map->getMap();
	Agents* agents;
	agents = agents->getAgents();
	

	pair<int, int>agentPosition;
	
	//agentnumber,<agentpositionX,Y>
	vector<pair<int, pair<int, int>>>route = {};//�o�H������

	 //�G�[�W�F���g�̐��������[�v
	for (int agentsnum = agents->ourAgents[0][0]; agentsnum < agentsnum+agents->ourAgents.size();agentsnum++) {
		//position��-1
		//�������Ȃ���json�Ƃ�hogehoge������肵�Â炢
		agentPosition.first = agents->ourAgents[agentsnum-agents->ourAgents[0][0]][1]-1;//x
		agentPosition.second = agents->ourAgents[agentsnum-agents->ourAgents[0][0]][2]-1;//y
		//agent�̏����ʒu
		route.push_back(make_pair(agentsnum,agentPosition));
		
		calculateEvalution(route,agentsnum,agentPosition,map->readTurn,0);
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
vector<int> Prefetching::calculateEvalution(vector<pair<int,pair<int,int>>>route,int agentnum,pair<int,int>agentPosition,int readTurn,int sum)
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
	return vector<int>();
}


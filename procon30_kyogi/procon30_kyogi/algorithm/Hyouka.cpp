#include"Hyouka.h"



int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };
vector<vector<int>> Hyouka::hyoukaKeisan()
{
	Map *map;
	map = map->getMap();
	Agents* agents;
	agents = agents->getAgents();
	

	pair<int, int>agentPosition;
	
	//agentnumber,<agentpositionX,Y>
	vector<pair<int, pair<int, int>>>route = {};//経路初期化

	 //エージェントの数だけループ
	for (int agentsnum = agents->ourAgents[0][0]; agentsnum < agents->ourAgents[0][agentsnum-1];agentsnum++) {
		
		agentPosition.first = agents->ourAgents[1][agentsnum-agents->ourAgents[0][0]];//x
		agentPosition.second = agents->ourAgents[2][agentsnum-agents->ourAgents[0][0]];//y
		//agentの初期位置
		route.push_back(make_pair(agentsnum,agentPosition));
		
		calculateEvalution(route,agentsnum,agentPosition,map->readTurn,0);
	}

	

	

	return vector<vector<int>>();
}


//point計算
int Hyouka::calculateScore(pair<int,int>agentPosition)
{
	Map *map;
	map = map->getMap();
	Field *field;
	field = field->getField();

	int sum = 0;

	if (agentPosition.first <= 0 || agentPosition.first > map->width || agentPosition.second <= 0 || agentPosition.second > map->vertical) {
		return -1;
	}
	else {
		sum = field->points[agentPosition.first - 1][agentPosition.second - 1];
	}

	return sum;
}

//経路計算
vector<int> Hyouka::calculateEvalution(vector<pair<int,pair<int,int>>>route,int agentnum,pair<int,int>agentPosition,int readTurn,int sum)
{		
	Map* map;
	map = map->getMap();
	
	rep(turn,9) {
		agentPosition.first += dx[turn];
		agentPosition.second += dy[turn];
		route.push_back(make_pair(agentnum, agentPosition));
		if (turn == 4) {}//移動しない
		else {
			sum += calculateScore(agentPosition);
		}
		if (readTurn >= 0) {
			readTurn--;
			calculateEvalution(route, agentnum,agentPosition,readTurn,sum);
		
		}
		else {

		}
	}
	return vector<int>();
}


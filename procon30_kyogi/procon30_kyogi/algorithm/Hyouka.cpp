#include"Hyouka.h"


//全てのエージェントについて一気に評価点計算をしたほうが
//場所変更などをしやすい

//評価点計算に必要な情報は
//フィールド情報、タイル状況、エージェントの位置
//自分のチームの得点、相手のチームの得点
//それぞれを引数として扱う


vector<vector<>>route = {};//経路初期化

int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };
vector<vector<int>> Hyouka::hyoukaKeisan()
{
	Map *map;
	map = map->getMap();
	Agents* agents;
	agents = agents->getAgents();
	

	pair<int, int>agentPosition;
	
	

	 //エージェントの数だけループ
	for (int agentsnum = agents->ourAgents[0][0]; agentsnum < agents->ourAgents[0][agentsnum-1];agentsnum++) {
		
		agentPosition.first = agents->ourAgents[1][agentsnum-agents->ourAgents[0][0]];//x
		agentPosition.second = agents->ourAgents[2][agentsnum-agents->ourAgents[0][0]];//y

		calculateEvalution(agentsnum,agentPosition,map->readTurn,0);
	}

	

	

	return vector<vector<int>>();
}


//point計算
int Hyouka::calculateScore(int x,int y)
{
	Map *map;
	map = map->getMap();
	Field *field;
	field = field->getField();

	int sum = 0;

	if (x <= 0 || x > map->width || y <= 0 || y > map->vertical) {
		return -1;
	}
	else {
		field->points[x - 1][y - 1];
	}

	return sum;
}

//経路計算
vector<int> Hyouka::calculateEvalution(int agentnum,pair<int,int>agentPosition,int readTurn,int turn)
{		
	Map* map;
	map = map->getMap();
	int toX, toY;
	
	rep(turn,9) {
		toX += dx[turn];
		toY += dy[turn];
		agentPosition.first
		calculateEvalution(agentnum,)
	}
	return vector<int>();
}


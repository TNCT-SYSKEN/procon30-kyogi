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
	vector<pair<int, pair<int, int>>>route = {};//経路初期化

	 //エージェントの数だけループ
	for (int agentsnum = agents->ourAgents[0][0]; agentsnum < agentsnum+agents->ourAgents.size();agentsnum++) {
		//positionに-1
		//そうしないとjsonとのhogehogeがやり取りしづらい
		agentPosition.first = agents->ourAgents[agentsnum-agents->ourAgents[0][0]][1]-1;//x
		agentPosition.second = agents->ourAgents[agentsnum-agents->ourAgents[0][0]][2]-1;//y
		//agentの初期位置
		route.push_back(make_pair(agentsnum,agentPosition));
		
		calculateEvalution(route,agentsnum,agentPosition,map->readTurn,0);
	}

	

	

	return vector<vector<int>>();
}


//point計算
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

//経路計算
vector<int> Prefetching::calculateEvalution(vector<pair<int,pair<int,int>>>route,int agentnum,pair<int,int>agentPosition,int readTurn,int sum)
{		
	Map* map;
	map = map->getMap();
	
	rep(turn,9) {

		//行けない方向に行こうとしたときに強制終了させる
		if (agentPosition.first + dx[turn] < 0 || agentPosition.first + dx[turn] >= map->width
			|| agentPosition.second + dy[turn] < 0 || agentPosition.second + dy[turn] >= map->vertical) {
			goto CantGoThere;
		}


		agentPosition.first += dx[turn];
		agentPosition.second += dy[turn];

		route.push_back(make_pair(agentnum, agentPosition));

		if (turn == 4) 
		{
		
		}//移動しない
		else {
			sum += calculateScore(agentPosition);
		}
		if (readTurn > 0) {
			readTurn--;
			//再帰
			calculateEvalution(route, agentnum,agentPosition,readTurn,sum);
		}
		else {
			//枝先(評価計算)
			Evalution evalution;
			evalution.calculateEvalution(route,sum);


			//route vectorの解放
			vector<pair<int, pair<int, int>>>().swap(route);
		}
	}

	//行けない方向に行こうとしたときに強制終了させる
	CantGoThere:;
	return vector<int>();
}


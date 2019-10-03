#include"Prefetching.h"
#include"Evalution.h"
#include"../Data/AgentsEvalution.h"

int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };
void Prefetching::hyoukaKeisan()
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
	vector<pair<int, pair<int, int>>>route = {};//経路初期化
	int ourAgentsS = agents->ourAgents.size();


	agentsEvalution->maxRoute.resize(agents->ourAgents.size(),vector<pair<int,pair<int,int>>>(map->readTurn));
	agentsAction->actionDxDy.resize(ourAgentsS);

	vector<pair<int, pair<int, int>>>moveUpTile;


	 //エージェントの数だけループ
	for (int agentsnum = agents->ourAgents[0][0]; agentsnum < agents->ourAgents[0][0]+ourAgentsS;agentsnum++) {
		//positionに-1
		//そうしないとjsonとのhogehogeがやり取りしづらい
		agentPosition.first = agents->ourAgents[agentsnum-agents->ourAgents[0][0]][1]-1;//x
		agentPosition.second = agents->ourAgents[agentsnum-agents->ourAgents[0][0]][2]-1;//y
		//agentの初期位置
		route.push_back(make_pair(agentsnum,agentPosition));
		

		//agentsEvalutionのmax評価値を初期化
		agentsEvalution->maxEvalutionPoint = 0;
		calculateEvalution(route,agentPosition,moveUpTile,0,map->readTurn,0);
		//
	


			//AgentsAction.hに書き込み
		agentsAction->actionDxDy[agentsnum - agents->ourAgents[0][0]].push_back(
			agentsEvalution->maxRoute[agentsnum-agents->ourAgents[0][0]][0]);

		
		if (agentsEvalution->maxRoute[agentsnum-agents->ourAgents[0][0]][0].second.first == 0 && 
			agentsEvalution->maxRoute[agentsnum-agents->ourAgents[0][0]][0].second.second == 0) {
			agentsAction->actionType[agentsnum - agents->ourAgents[0][0]].push_back(0);
		}
		else {
			agentsAction->actionType[agentsnum - agents->ourAgents[0][0]].push_back(1);
		}

	}
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
void  Prefetching::calculateEvalution(vector<pair<int,pair<int,int>>>route, pair<int, int> nowAgentPosition,
	vector<pair<int, pair<int, int>>>moveUpTile, int moveup, int readTurn,int sum)
{		
	Map* map;
	map = map->getMap();
	Field* field;
	field = field->getField();

	
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
		//踏んだのが自分チームのタイルだったらアクセスしない
		if (movedTiled[nowAgentPosition.first + dx[turn]][nowAgentPosition.second + dy[turn]] == map->ourTeamID) {
			if (turn != 4) {

				goto CantGoThere;
			}
		}

		if (turn == 4) {

		}
		else {


			if (movedTiled[nowAgentPosition.first + dx[turn]][nowAgentPosition.second + dy[turn]] == map->otherTeamID) {
				//moveupのresize

				if (readTurn > 0) {
					moveUpTile.resize(moveup + 1);

					//1,2,3,4,5
					moveUpTile[moveup] = make_pair(map->finalTurn - map->turn + 1 - readTurn,
						make_pair(nowAgentPosition.first + dx[turn], nowAgentPosition.second + dy[turn]));
					moveup++;
					moveCheck = true;
					movedTiled[nowAgentPosition.first + dx[turn]][nowAgentPosition.second + dy[turn]];
					sum += calculateScore(make_pair(nowAgentPosition.first + dx[turn], nowAgentPosition.second + dy[turn]));
				}

			}
			else {

				nowAgentPosition.first += dx[turn];
				nowAgentPosition.second += dy[turn];
			}
		}
		//routeサイズ調整


		if (readTurn > 0) {

			route.resize(route.size() + 1);
			route.push_back(make_pair(route[0].first, make_pair(dx[turn], dy[turn])));
			readTurn--;
			calculateEvalution(route, nowAgentPosition, moveUpTile, moveup, readTurn, sum);
		}
		else {
			Evalution evalution;
			evalution.calculateEvalution(route, moveUpTile, moveup, sum);

		}


		//ひとつ前を消す
		route.resize(route.size() - 1);
	CantGoThere:;
	}

}


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
	vector<pair<int, pair<int, int>>>route;//経路初期化
	int ourAgentsS = agents->ourAgents.size();
	

	agentsEvalution->maxRoute.resize(agents->ourAgents.size(),vector<pair<int,pair<int,int>>>(map->readTurn));
	agentsAction->actionDxDy.resize(ourAgentsS);

	vector<pair<int, pair<int, int>>>moveUpTile;
	
	int Agent0 = agents->ourAgents[0][0];

	 //エージェントの数だけループ
	for (int agentsnum = Agent0; agentsnum < (Agent0 + ourAgentsS); agentsnum++) {
		//positionに-1	
		//そうしないとjsonとのhogehogeがやり取りしづらい
		agentPosition =make_pair((agents->ourAgents[agentsnum - Agent0][1]-1), (agents->ourAgents[agentsnum - Agent0][2]-1));//

		
			//agentの初期位置
		route.push_back(make_pair(agentsnum, agentPosition));

		//agentsEvalutionのmax評価値を初期化
		agentsEvalution->maxEvalutionPoint = 0;
		calculateEvalution(route, agentPosition, moveUpTile, 0, map->readTurn, 0);
		
		route.resize(route.size() - 1);

		agentsAction->actionType.resize(ourAgentsS);
			//AgentsAction.hに書き込み
		agentsAction->actionDxDy.resize(ourAgentsS);
		
		agentsEvalution->maxEvalutionPoint=0;
		rep(i,map->readTurn) {

			agentsAction->actionDxDy[agentsnum - Agent0].push_back(
				agentsEvalution->maxRoute[agentsnum - Agent0][i]);

			if (agentsEvalution->maxRoute[agentsnum - Agent0][i].second.first == 0 &&
				agentsEvalution->maxRoute[agentsnum - Agent0][i].second.second == 0) {
				//stay
				agentsAction->actionType[agentsnum - Agent0].push_back(0);
			}
			else if (field->tiled[(agents->ourAgents[agentsnum-Agent0][1]-1)+(agentsEvalution->maxRoute[agentsnum-Agent0][i].second.first)]
			[(agents->ourAgents[agentsnum - Agent0][2]-1) + (agentsEvalution->maxRoute[agentsnum - Agent0][i].second.second)] == map->otherTeamID){
				//remove
				agentsAction->actionType[agentsnum - Agent0].push_back(-1);
			}
			else {
				//move
				agentsAction->actionType[agentsnum - Agent0].push_back(1);
			}
		}

	}

}


//point計算
int Prefetching::calculateScore(pair<int,int>agentPosition,int turn)
{
	Map *map;
	map = map->getMap();
	Field *field;
	field = field->getField();

	int sum = 0;
	if (turn == 4) {
		return 0;
	}
	else if (agentPosition.first < 0 || agentPosition.first >= map->width || agentPosition.second < 0 || agentPosition.second >= map->vertical) {
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
	
	int dx[9] = { 1,1,1,0,0,0,-1,-1,-1 };
	int dy[9] = { 1,0,-1,1,0,-1,1,0,-1 };
	Map* map;
	map = map->getMap();
	
	Field* field;
	field = field->getField();

	int Dx=nowAgentPosition.first, Dy=nowAgentPosition.second;
	
	bool moveCheck = false;

	int movedTiled[20][20];
	rep(i, map->width) {
		rep(j, map->vertical) {
			movedTiled[i][j] = field->tiled[i][j];
		}
	}

	rep(turn, 9) {
		Dx = nowAgentPosition.first;
		Dy = nowAgentPosition.second;
		
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
					//moveUpTile.resize(moveup + 1);

					////1,2,3,4,5
					//moveUpTile[moveup] = make_pair(map->finalTurn - map->turn + 1 - readTurn,
					//	make_pair(nowAgentPosition.first + dx[turn], nowAgentPosition.second + dy[turn]));
					//moveup++;
					//moveCheck = true;
					//movedTiled[nowAgentPosition.first + dx[turn]][nowAgentPosition.second + dy[turn]];
					sum += calculateScore(make_pair(nowAgentPosition.first + dx[turn], nowAgentPosition.second + dy[turn]),turn);
				}

			}
			else {
				//////error
				Dx+= dx[turn];
				Dy+= + dy[turn];
			}
			sum += calculateScore(make_pair(nowAgentPosition.first + dx[turn], nowAgentPosition.second + dy[turn]), turn);
		}
		//routeサイズ調整


		if (readTurn > 1) {
			
			route.push_back(make_pair(route[0].first, make_pair(dx[turn], dy[turn])));
			readTurn--;
		
				calculateEvalution(route, make_pair(Dx,Dy), moveUpTile, moveup, readTurn, sum);
				//route.resize(route.size() - 1);
		
		}else if (readTurn==1){
			route.push_back(make_pair(route[0].first, make_pair(dx[turn], dy[turn])));
			Evalution evalution;
			evalution.calculateEvalution(route, moveUpTile, moveup, sum);
			route.resize(route.size() - 1);
		}
		
	

		//ひとつ前を消す
		
	CantGoThere:;
	}

}


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
	

	//maxRoute,actionDXDYの初期化
	agentsEvalution->maxRoute.resize(0);
	agentsEvalution->maxRoute.resize(agents->ourAgents.size());
	agentsAction->actionDxDy.resize(0);
	agentsAction->actionDxDy.resize(ourAgentsS,vector<pair<int,pair<int,int>>>(0));

	agentsAction->actionType.resize(0);
	agentsAction->actionType.resize(ourAgentsS);


	int Agent0 = agents->ourAgents[0][0];



	 //エージェントの数だけループ
	for (int agentsnum = 0; agentsnum < ourAgentsS; agentsnum++) {
		//positionに-1	
		//そうしないとjsonとのhogehogeがやり取りしづらい
		agentPosition =make_pair((agents->ourAgents[agentsnum][1]-1), (agents->ourAgents[agentsnum][2]-1));//

		
			//agentの初期位置
		route.push_back(make_pair(agents->ourAgents[agentsnum][0], agentPosition));

		//agentsEvalutionのmax評価値を初期化
		agentsEvalution->maxEvalutionPoint = -100;
		
		//タイル状態
		vector<vector<int>> moveUpTile;
		moveUpTile.resize(20, vector<int>(20));
		rep(i, map->width) {
			rep(j, map->vertical) {
				moveUpTile[i][j] = field->tiled[i][j];
			}
		}
														//何番目に計算
		calculateEvalution(route, agentPosition, moveUpTile, agentsnum, map->readTurn, 0);
		
		route.resize(0);

		
			//AgentsAction.hに書き込み
		agentsAction->actionDxDy[agentsnum].resize(0);
		
		agentsEvalution->maxEvalutionPoint=-100;
		
		

		rep(i,map->readTurn) {

			agentsAction->actionDxDy[agentsnum].push_back(
				agentsEvalution->maxRoute[agentsnum][i]);
			if (agentsEvalution->maxRoute[agentsnum][i].second.first == 0 &&
				agentsEvalution->maxRoute[agentsnum][i].second.second == 0) {
				//stay
				agentsAction->actionType[agentsnum].push_back(0);
				
			}
			else if (field->tiled[(agents->ourAgents[agentsnum][1]-1)+(agentsEvalution->maxRoute[agentsnum][i].second.first)]
			[(agents->ourAgents[agentsnum][2]-1) + (agentsEvalution->maxRoute[agentsnum][i].second.second)] == map->otherTeamID){
				//remove
				agentsAction->actionType[agentsnum].push_back(-1);
				
			}
			else {
				//move
				agentsAction->actionType[agentsnum].push_back(1);
				
			}
			//map->score[1][1]++;
		}


		//map->score[1][2] += agentsEvalution->maxRoute[agentsnum].size();

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
		return -3;
	}
	else if (field->tiled[agentPosition.first][agentPosition.second]==map->ourTeamID) {
		return -10;
	}
	else {
		sum = field->points[agentPosition.first][agentPosition.second];
	}

	return sum;
}

//経路計算
void  Prefetching::calculateEvalution(vector<pair<int,pair<int,int>>>route, pair<int, int> nowAgentPosition,
	vector<vector<int>>moveUpTile, int agentsnum, int readTurn,int sum)
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
	int Dx=nowAgentPosition.first, Dy=nowAgentPosition.second;
	int giveReadTurn;

	bool moveCheck = false;

	

	int nowX,nowY;


	rep(turn, 9) {
		Dx = nowAgentPosition.first;
		Dy = nowAgentPosition.second;
		

		/*一部の計算を除外する部分（処理軽量化のため）*/
		
		//nowX = route[0].second.first;
		//nowY = route[0].second.second;

		
			//画面外
		if (Dx + dx[turn] < 0 || Dx + dx[turn] >= map->width || Dy + dy[turn] < 0 || Dy + dy[turn] >= map->vertical) {
			goto fini;
		}

		//移動先に味方エージェントがいるかどうか
		rep(i, agents->ourAgents.size()) {
			if (Dx + dx[turn] == agents->ourAgents[agentsnum][1] && 
				Dy + dy[turn] == agents->ourAgents[agentsnum][2]) {

				goto fini;
			}
		}

		//戻ろうとするときの除外
		//dx,dyが入ってるとき

		//移動先が自分チーム（戻るも含まれる）
		if (moveUpTile[Dx + dx[turn]][Dy + dy[turn]] == map->ourTeamID) {
			goto fini;
		}

		//移動先が相手チームタイルだったら
		else if (moveUpTile[Dx + dx[turn]][Dy + dy[turn]] == map->otherTeamID) {

			moveUpTile[Dx + dx[turn]][Dy + dy[turn]] = 0;
			Dx -= dx[turn];
			Dy -= dy[turn];
		}
		

		//位置更新
		Dx += dx[turn];
		Dy += dy[turn];

		if (readTurn > 1) {
			
			route.push_back(make_pair(route[0].first, make_pair(dx[turn], dy[turn])));
			giveReadTurn = readTurn-1;
		
			calculateEvalution(route, make_pair(Dx,Dy), moveUpTile, agentsnum, giveReadTurn, sum);
				route.resize(route.size() - 1);
		
		}else if (readTurn==1){
			route.push_back(make_pair(route[0].first, make_pair(dx[turn], dy[turn])));
			/*nowX = route[0].second.first;
			nowY = route[0].second.second;
			rep(Checkturn, map->readTurn) {
				nowX += route[Checkturn + 1].second.first;
				nowY += route[Checkturn + 1].second.second;

				if (nowX < 0 || nowX >= map->width || nowY < 0 || nowY >= map->vertical) {
					route.resize(route.size() - 1);
					goto fini;
				}
				if (moveUpTile[nowX][nowY] == map->ourTeamID) {
					
					nowX -= route[Checkturn + 1].second.first;
					nowY -= route[Checkturn + 1].second.second;

					route.resize(route.size() - 1);
					goto fini;

				}if (moveUpTile[nowX][nowY] == map->otherTeamID) {
					moveUpTile[nowX][nowY] = 0;
					nowX -= route[Checkturn + 1].second.first;
					nowY -= route[Checkturn + 1].second.second;
				}
				else {

				}

			}*/
			
			
			evalution.calculateEvalution(route,moveUpTile, agentsnum, sum);
			route.resize(route.size() - 1);
		}
		
	
		//route.resize(route.size() - 1);
		//routeSizeのためにエージェントの位置が範囲外でもpushしてからでないとnull参照を起こすから、
		//push_backすべき


		//ひとつ前を消す
		
		fini:;
	}

}


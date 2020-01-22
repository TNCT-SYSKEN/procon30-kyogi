#include"Prefetching.h"
#include"Evalution.h"
#include"../Data/AgentsEvalution.h"


void Prefetching::prefetching()
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
	agentsEvalution->maxRoute.resize(agents->ourAgents.size(), vector<pair<int, pair<int, int>>>(0));
	

	agentsAction->actionType.resize(0);
	agentsAction->actionType.resize(ourAgentsS);

	// turn ごとのタイル状況
	vector<vector<vector<int>>> moveUpTile;
	moveUpTile.resize(map->readTurn, vector<vector<int>>(map->width, vector<int>(map->vertical)));
	rep(i, map->width) {
		rep(j, map->vertical) {
			moveUpTile[0][i][j] = field->tiled[i][j];
		}
	}


	//エージェントの数だけループ
	for (int agentsnum = 0; agentsnum < ourAgentsS; agentsnum++) {
		//
		agentPosition = make_pair((agents->ourAgents[agentsnum][1]), (agents->ourAgents[agentsnum][2]));//


			//agentの初期位置
		route.push_back(make_pair(agents->ourAgents[agentsnum][0], agentPosition));

		//agentsEvalutionのmax評価値を初期化
		agentsEvalution->maxEvalutionPoint = mINF;


		//何番目に計算
		calculateEvalution(route, agentPosition, moveUpTile, agentsnum, map->readTurn, 0);

		route.resize(0);


		/*ここまで見た*/
		/////////////////////////////////////////////////////////
		//AgentsAction.hに書き込み
		agentsAction->actionDxDy[agentsnum].resize(0);
		agentsEvalution->maxEvalutionPoint = mINF;

	}

	//　移動先重複確認
	changeDestination();
	

	//移動先決定 and 書き込み
	for(int agentsnum=0;agentsnum<ourAgentsS;agentsnum++){
		//
		int nowX = agents->ourAgents[agentsnum][1];
		int nowY = agents->otherAgents[agentsnum][2];

		rep(i, map->readTurn) {
			// 動いた後のPosition
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
				// moveUpTileに更新
				// 後のターンのタイルにも反映
				for (int tmp = i; i < map->readTurn; i++) {
					moveUpTile[tmp + 1][nowX][nowY] = 0;
				}
				
				nowX -= agentsEvalution->maxRoute[agentsnum][i].second.first;
				nowY -= agentsEvalution->maxRoute[agentsnum][i].second.second;
			}
			else {
				//move	
				// moveUpTileに更新
				// 後のターンのタイルにも反映
				for (int tmp = i; i < map->readTurn; i++) {
					moveUpTile[tmp + 1][nowX][nowY] = map->ourTeamID;
				}
				agentsAction->actionType[agentsnum].push_back(1);

			}
		}
	}





}



//経路計算
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


			//画面外
		if (Dx + dx[turn] < 0 || Dx + dx[turn] >= map->width || Dy + dy[turn] < 0 || Dy + dy[turn] >= map->vertical) {
			goto fini;
		}

		//戻ろうとするときの除外
		//dx,dyが入ってるとき

		//移動先が自分チーム（戻るも含まれる）
		if (moveUpTile[map->readTurn-readTurn][Dx + dx[turn]][Dy + dy[turn]] == map->ourTeamID) {
			// sum を減らすかも
		}
		//移動先が相手チームタイルだったら
		else if (moveUpTile[map->readTurn-readTurn][Dx + dx[turn]][Dy + dy[turn]] == map->otherTeamID) {

			moveUpTile[map->readTurn-readTurn][Dx + dx[turn]][Dy + dy[turn]] = 0;
			Dx -= dx[turn];
			Dy -= dy[turn];

		}
		else {
			// tile	を塗る	
			moveUpTile[map->readTurn-readTurn][Dx + dx[turn]][Dy + dy[turn]] = map->ourTeamID;

		}


		//位置更新
		Dx += dx[turn];
		Dy += dy[turn];

		//先読みターン数(readTurn)を再帰で呼び出すたびに-1
		if (readTurn > 1) {
			route.push_back(make_pair(route[0].first, make_pair(dx[turn], dy[turn])));
			giveReadTurn = readTurn - 1;


			calculateEvalution(route, make_pair(Dx, Dy), moveUpTile, agentsnum, giveReadTurn, sum);
			route.resize(route.size() - 1);

		}
		else if (readTurn == 1) {
			route.push_back(make_pair(route[0].first, make_pair(dx[turn], dy[turn])));

			//評価計算
			evalution.calculateEvalution(route, moveUpTile, agentsnum, sum);
			route.resize(route.size() - 1);
		}


		//route.resize(route.size() - 1);
		//routeSizeのためにエージェントの位置が範囲外でもpushしてからでないとnull参照を起こすから、
		//push_backすべき

	fini:;
	}

}



void Prefetching::changeDestination() {
	Map* map;
	map = map->getMap();
	Agents* agents;
	agents = agents->getAgents();
	AgentsEvalution *agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();
	AgentsAction *agentsAction;
	agentsAction = agentsAction->getAgentsAction();
	Field* field;
	field = field->getField();

	pair<int, int>mainAgent;
	pair<int, int>partnerAgent;
	
	// defalutは現在4ターン設定
	int useReadTurn = map->maxLimitReadTurn;
	// 範囲外アクセスのエラーを防ぐ
	if (map->readTurn < map->maxLimitReadTurn) {
		useReadTurn = map->readTurn;
	}

	//turn->x->y->visitedAgentCounter
	vector<vector<vector<vector<int>>>> movedTileAgent(useReadTurn,vector<vector<vector<int>>>(map->width,vector<vector<int>>(map->vertical)));
	// turn->x->y
	vector<vector<vector<int>>> turnTiled(useReadTurn + 1, vector<vector<int>>(map->width, vector<int>(map->vertical)));


	rep(turn, useReadTurn) {
		turnTiled[turn] = field->tiled;
	}


	// 2回同じペアを計算しないように重複判定を行う
	rep(main, agents->ourAgents.size() - 1) {
		for (int partner = main + 1; partner < agents->ourAgents.size; partner++) {
			
			mainAgent = make_pair(agents->ourAgents[main][1], agents->ourAgents[main][2]);
			partnerAgent = make_pair(agents->ourAgents[partner][1], agents->ourAgents[partner][2]);

			//調べる　先読みターン 1 ~ readTurn
			//先読みターン数を大きくしすぎたら「まずい」からいったん上限を4にする
			rep(turn, useReadTurn) {
				mainAgent.first += agentsEvalution->maxRoute[main][turn].second.first;
				mainAgent.second += agentsEvalution->maxRoute[main][turn].second.second;
				
				partnerAgent.first += agentsEvalution->maxRoute[partner][turn].second.first;
				partnerAgent.second += agentsEvalution->maxRoute[partner][turn].second.second;

				// 一致したら
				if (mainAgent == partnerAgent) {
					bool mainCheck = false;
					bool partnerCheck = false;
					rep(count, movedTileAgent[turn][mainAgent.first][mainAgent.second].size()) {
						
						if (movedTileAgent[turn][mainAgent.first][mainAgent.second][count] == main) {
							mainCheck = true;
						}
						if(	movedTileAgent[turn][mainAgent.first][mainAgent.second][count] == partner){ 
							partnerCheck = true;
						}
					}
					// if mainCheck != true
					if (!mainCheck) {
						movedTileAgent[turn][mainAgent.first][mainAgent.second].push_back(main);
					}
					if (!partnerCheck) {
						movedTileAgent[turn][mainAgent.first][mainAgent.second].push_back(partner);
					}
				}

				if (turn + 1 < useReadTurn) {
					// 相手タイル除去判定の計算
					if (turnTiled[turn][mainAgent.first][mainAgent.second] == map->otherTeamID) {
						//	次のターンのフィールドに更新
						turnTiled[turn + 1][mainAgent.first][mainAgent.second] = 0;
						// タイル除去ではエージェントの位置は動かない
						mainAgent.first -= agentsEvalution->maxRoute[main][turn].second.first;
						mainAgent.second -= agentsEvalution->maxRoute[main][turn].second.second;
					}
					if (turnTiled[turn][partnerAgent.first][partnerAgent.second] == map->otherTeamID) {
						//	次のターンのフィールドに更新
						turnTiled[turn + 1][partnerAgent.first][partnerAgent.second] = 0;
						// タイル除去ではエージェントの位置は動かない
						partnerAgent.first -= agentsEvalution->maxRoute[partner][turn].second.first;
						partnerAgent.second -= agentsEvalution->maxRoute[partner][turn].second.second;
					}
				}
			}
		}
	}

	// 重複判定完了


}
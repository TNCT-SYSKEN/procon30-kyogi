#include"Prefetching.h"
#include"Evalution.h"
#include"../Data/AgentsEvalution.h"


void Prefetching::prefetching()
{
	int dx[9] = { 1,1,1,0,0,0,-1,-1,-1 };
	int dy[9] = { 1,0,-1,1,0,-1,1,0,-1 };

	//限られたターンの中でどうやって最高評価点を出すか

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
	
	Evalution evalution;


	// <turn1(dX,dY),turn2(dx,dy)>
	// route の定義
	vector<vector<pair<int, int>>>route(agents->ourAgents.size());
	
	// 3手のビームサーチ候補
	vector<vector<pair<int, int>>>fork(agents->ourAgents.size());
	

	// agentsEvalutionのturnTiledFieldの初期化
	agentsEvalution->turnTiledField.resize(map->width,vector<int>(map->vertical));
	agentsEvalution->turnTiledField = field->tiled;
	
	// agentの現在位置 calculatePrefetchingで使う
	vector<pair<int, int>> beforeAgentsPosition;
	rep(num, agents->ourAgents.size()) {
		beforeAgentsPosition.push_back(make_pair(agents->ourAgents[num][1], agents->ourAgents[num][2]));
	}


	//forkでの評価値記録
	vector<vector<float>> evalutionAgentPoint(agents->ourAgents.size());


	//最初の3手を決定
	rep(num, agents->ourAgents.size()) {

		priority_queue<pair<float, pair<int, int>>> Pqueue;
		
		rep(counter, 9) {

			int nowX = agents->ourAgents[num][1] + dx[counter];
			int nowY = agents->ourAgents[num][2] + dy[counter];

			// 範囲外計算
			if (nowX >= map->width || nowX < 0 || nowY >= map->vertical || nowY < 0) {
				Pqueue.push(make_pair(mINF,make_pair(dx[counter],dy[counter])));
			}
			// evalutionFieldの値を代入
			else {
				float evalutionP = evalution.calculateEvalutionPoint(nowX, nowY, beforeAgentsPosition);
				Pqueue.push(make_pair(evalutionP, make_pair(dx[counter], dy[counter])));
			}
		}
		//上位3手を選択
		rep(tmp, 3) {
			// 評価値記録
			evalutionAgentPoint[num].push_back(Pqueue.top().first);
			// x,y の代入
			fork[num].push_back(Pqueue.top().second);
			Pqueue.pop();
		}
	}





	//maxRoute,actionDXDYの初期化
	agentsEvalution->maxRoute.resize(0);
	agentsEvalution->maxRoute.resize(agents->ourAgents.size(), vector<pair<int, int>>(0));
	

	agentsAction->actionType.resize(0);
	agentsAction->actionType.resize(agents->ourAgents.size());

	//agentsEvalutionのmax評価値を初期化
	agentsEvalution->maxEvalutionPoint = mINF;


	// moveUpTileの定義
	vector<vector<int>> moveUpTile(map->width,vector<int>(map->vertical));
	rep(i, map->width) {
		rep(j, map->vertical) {
			moveUpTile[i][j] = field->tiled[i][j];
		}
	}

	/******************新規記入****************/

	
	// agentの数nビット、ビームサーチ探索mのm進数ビット列で考える
	int maxBit = (agents->ourAgents.size() + 1 )* 3;

	rep(bit, maxBit) {

		float sumEvalution = 0;

		//routeにpush
		rep(num, agents->ourAgents.size()) {

			// num Bit右にシフトさせて一つ上の位の値で割った余りを出す
			int POS = (bit / (bit^num)) % (bit ^ (num + 1));
			
			//サイズを +1
			route[num].push_back(fork[num][POS]);
			sumEvalution += evalutionAgentPoint[num][POS];
		}

		// 計算
		calculatePrefetching(route, beforeAgentsPosition, moveUpTile, map->readTurn - 1, sumEvalution);

		// route からpop
		rep(num, agents->ourAgents.size()) {
			// サイズを -1
			route[num].resize(route[num].size() - 1);
		}
	}




	//　移動先重複確認
	changeDestination();
	



	//移動先決定 and 書き込み
	rep(num, agents->ourAgents.size()) {
		//
		int nowX = agents->ourAgents[num][1];
		int nowY = agents->otherAgents[num][2];

		agentsAction->actionDxDy[num].resize(0);


		rep(i, map->readTurn) {
			// 動いた後のPosition
			nowX += agentsEvalution->maxRoute[num][i].first;
			nowY += agentsEvalution->maxRoute[num][i].second;

			// actionDxDyにpush
			agentsAction->actionDxDy[num].push_back(make_pair(agents->ourAgents[num][0], agentsEvalution->maxRoute[num][i]));


			if (agentsEvalution->maxRoute[num][i].first == 0 &&
				agentsEvalution->maxRoute[num][i].second == 0) {
				//stay
				agentsAction->actionType[num].push_back(0);

			}
			else if (moveUpTile[nowX][nowY] == map->otherTeamID) {
				//remove
				agentsAction->actionType[num].push_back(-1);
				// moveUpTileに更新

				moveUpTile[nowX][nowY] = 0;

				nowX -= agentsEvalution->maxRoute[num][i].first;
				nowY -= agentsEvalution->maxRoute[num][i].second;
			}
			else {
				//move	
				// moveUpTileに更新

				moveUpTile[nowX][nowY] = map->ourTeamID;
				agentsAction->actionType[num].push_back(1);

			}
		}
	}
}



//経路計算
void  Prefetching::calculatePrefetching(vector<vector<pair<int, int>>>route, vector<pair<int, int>> beforeAgentsPosition,
	vector<vector<int>>moveUpTile, int readTurn, float sumOfEvalution)
{
	int dx[9] = { 1,1,1,0,0,0,-1,-1,-1 };
	int dy[9] = { 1,0,-1,1,0,-1,1,0,-1 };

	Map* map;
	map = map->getMap();
	Agents* agents;
	agents = agents->getAgents();
	Field* field;
	field = field->getField();
	AgentsEvalution* agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();
	Evalution evalution;


	// 重複しないなら
	if (checkCollision(route,beforeAgentsPosition)) {

		//まだ計算するなら
		if (readTurn > 0) {
			
			// beforeAgentPositionの位置更新
			rep(num, agents->ourAgents.size()) {
				int routeCalcS = route[0].size - 1;
				int PosX = beforeAgentsPosition[num].first + route[num][routeCalcS].first;
				int PosY = beforeAgentsPosition[num].second + route[num][routeCalcS].second;

				// タイルふみ
				if (field->tiled[PosX][PosY] == map->ourTeamID) {
					beforeAgentsPosition[num].first += route[num][routeCalcS].first;
					beforeAgentsPosition[num].second += route[num][routeCalcS].second;
				}
				else if (field->tiled[PosX][PosY] == 0) {
					beforeAgentsPosition[num].first += route[num][routeCalcS].first;
					beforeAgentsPosition[num].second += route[num][routeCalcS].second;
					moveUpTile[PosX][PosY] = map->ourTeamID;
				}
				else {
					moveUpTile[PosX][PosY] = 0;
				}
			}

			// moveUpTile を反映
			agentsEvalution->turnTiledField = moveUpTile;


			// 3手のビームサーチ候補
			vector<vector<pair<int, int>>>fork(agents->ourAgents.size());
			//forkでの評価値記録
			vector<vector<float>> evalutionAgentPoint(agents->ourAgents.size());


			//最初の3手を決定
			rep(num, agents->ourAgents.size()) {

				priority_queue<pair<float, pair<int, int>>> Pqueue;

				rep(counter, 9) {

					int nowX = beforeAgentsPosition[num].first + dx[counter];
					int nowY = beforeAgentsPosition[num].second + dy[counter];

					// 範囲外計算
					if (nowX >= map->width || nowX < 0 || nowY >= map->vertical || nowY < 0) {
						Pqueue.push(make_pair(mINF, make_pair(dx[counter], dy[counter])));
					}
					// evalutionFieldの値を代入
					else {
						float evalutionP = evalution.calculateEvalutionPoint(nowX, nowY,beforeAgentsPosition);
						Pqueue.push(make_pair(evalutionP, make_pair(dx[counter], dy[counter])));
					}
				}
				//上位3手を選択
				rep(tmp, 3) {
					// 評価値記録
					evalutionAgentPoint[num].push_back(Pqueue.top().first);
					// x,y の代入
					fork[num].push_back(Pqueue.top().second);
					Pqueue.pop();
				}
			}


			// agentの数nビット、ビームサーチ探索mのm進数ビット列で考える
			int maxBit = (agents->ourAgents.size() + 1) * 3;

			rep(bit, maxBit) {

				float sumEvalution = 0;

				//routeにpush
				rep(num, agents->ourAgents.size()) {

					// num Bit右にシフトさせて一つ上の位の値で割った余りを出す
					int POS = (bit / (bit^num)) % (bit ^ (num + 1));

					//サイズを +1
					route[num].push_back(fork[num][POS]);
					sumEvalution += evalutionAgentPoint[num][POS];
				}

				// 計算
				calculatePrefetching(route, beforeAgentsPosition, moveUpTile, map->readTurn - 1, sumEvalution + sumOfEvalution);

				// route からpop
				rep(num, agents->ourAgents.size()) {
					// サイズを -1
					route[num].resize(route[num].size() - 1);
				}
			}
		}
		else {
			// n番目に良いルートであるかを比較する
			evalution.calculateEvalution(route,sumOfEvalution);
		}
	}
}





// 移動先重複チェック
bool checkCollision(vector<vector<pair<int,int>>>route,vector<pair<int, int>> beforeAgentPos) {
	Map* map;
	map = map->getMap();
	Agents* agents;
	agents = agents->getAgents();

	int accessRouteSize = route[0].size() - 1;

	rep(main, agents->ourAgents.size()) {
		int mainX = beforeAgentPos[main].first + route[main][accessRouteSize].first;
		int mainY = beforeAgentPos[main].second + route[main][accessRouteSize].second;

		rep(partner, agents->ourAgents.size()) {
			int partnerX = beforeAgentPos[partner].first + route[partner][accessRouteSize].first;
			int partnerY = beforeAgentPos[partner].second + route[partner][accessRouteSize].second;

			if (main == partner) {
				continue;
			}
			if (mainX == partnerX && mainY == partnerY) {
				return false;
			}
		}

		if (mainX < 0 || mainX >= map->width || mainY < 0 || mainY >= map->vertical) {
			return false;
		}
	}

	return true;
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
	vector<vector<vector<vector<int>>>> turnMovedTileAgent(useReadTurn,vector<vector<vector<int>>>(map->width,vector<vector<int>>(map->vertical)));
	//x->y->visitedAgentCounter
	//push_backで追加
	vector<vector<int>> movedTiledCounter(map->width,vector<int>(map->vertical));
	// turn->x->y
	vector<vector<vector<int>>> turnTiled(useReadTurn + 1, vector<vector<int>>(map->width, vector<int>(map->vertical)));


	rep(turn, useReadTurn) {
		turnTiled[turn] = field->tiled;
	}
	/*

	// 2回同じペアを計算しないように重複判定を行う
	rep(main, agents->ourAgents.size() - 1) {
		for (int partner = main + 1; partner < agents->ourAgents.size; partner++) {
			
			mainAgent = make_pair(agents->ourAgents[main][1], agents->ourAgents[main][2]);
			partnerAgent = make_pair(agents->ourAgents[partner][1], agents->ourAgents[partner][2]);

			//調べる　先読みターン 1 ~ readTurn
			//先読みターン数を大きくしすぎたら「まずい」からいったん上限を4にする
			rep(turn, useReadTurn) {
				mainAgent.first += agentsEvalution->maxRoute[main][turn].first;
				mainAgent.second += agentsEvalution->maxRoute[main][turn].second;
				
				partnerAgent.first += agentsEvalution->maxRoute[partner][turn].first;
				partnerAgent.second += agentsEvalution->maxRoute[partner][turn].second;


				// check
				bool mainCheck = false;
				bool partnerCheck = false;

				// 
				rep(count, turnMovedTileAgent[turn][mainAgent.first][mainAgent.second].size()) {
						
					if (turnMovedTileAgent[turn][mainAgent.first][mainAgent.second][count] == main) {
						mainCheck = true;
					}
					if(	turnMovedTileAgent[turn][partnerAgent.first][partnerAgent.second][count] == partner){ 
						partnerCheck = true;
					}
				}
				// if mainCheck != true
				if (!mainCheck) {
					turnMovedTileAgent[turn][mainAgent.first][mainAgent.second].push_back(main);
				}
				if (!partnerCheck) {
					turnMovedTileAgent[turn][partnerAgent.first][partnerAgent.second].push_back(partner);
					}
				

				if (turn + 1 < useReadTurn) {
					// 相手タイル除去判定の計算
					if (turnTiled[turn][mainAgent.first][mainAgent.second] == map->otherTeamID) {
						for (int turnCount = turn; turnCount < useReadTurn - 1; turnCount++) {
							//	次のターンのフィールドに更新
							turnTiled[turn + 1][mainAgent.first][mainAgent.second] = 0;
						}
						// タイル除去ではエージェントの位置は動かない
						mainAgent.first -= agentsEvalution->maxRoute[main][turn].second.first;
						mainAgent.second -= agentsEvalution->maxRoute[main][turn].second.second;
					}
					if (turnTiled[turn][partnerAgent.first][partnerAgent.second] == map->otherTeamID) {
						for (int turnCount = turn; turnCount < useReadTurn - 1; turnCount++) {
							//	次のターンのフィールドに更新
							turnTiled[turn + 1][partnerAgent.first][partnerAgent.second] = 0;
						}
							// タイル除去ではエージェントの位置は動かない
						partnerAgent.first -= agentsEvalution->maxRoute[partner][turn].second.first;
						partnerAgent.second -= agentsEvalution->maxRoute[partner][turn].second.second;
					}



				}
			}
		}
	}
	*/
	// 重複判定完了
	
	//agentfield作成しようか

	//ここからややこしくなる






}
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
				float evalutionP = evalution.calculateEvalutionPoint(nowX, nowY);
				Pqueue.push(make_pair(evalutionP, make_pair(dx[counter], dy[counter])));
			}
		}
		//上位3手を選択
		rep(tmp, 3) {
			fork[num].push_back(Pqueue.top().second);
			Pqueue.pop();
		}
	}





	//maxRoute,actionDXDYの初期化
	agentsEvalution->maxRoute.resize(0);
	agentsEvalution->maxRoute.resize(agents->ourAgents.size(), vector<pair<int, pair<int, int>>>(0));
	

	agentsAction->actionType.resize(0);
	agentsAction->actionType.resize(agents->ourAgents.size());




	// moveUpTileの定義
	vector<vector<int>> moveUpTile(map->width,vector<int>(map->vertical));
	rep(i, map->width) {
		rep(j, map->vertical) {
			moveUpTile[i][j] = field->tiled[i][j];
		}
	}

	/******************新規記入****************/

	// agentの現在位置 calculatePrefetchingで使う
	vector<pair<int, int>> beforeAgentsPosition;
	rep(num, agents->ourAgents.size()) {
		beforeAgentsPosition.push_back(make_pair(agents->ourAgents[num][1], agents->ourAgents[num][2]));
	}


	rep(num, agents->ourAgents.size()) {
		rep(FORK, fork[num].size()) {

			//サイズを +1
			route[num].push_back(fork[num][FORK]);
			
			// 計算
			calculatePrefetching(route, beforeAgentsPosition, moveUpTile, map->readTurn-1);

			// サイズを -1
			route[num].resize(route[num].size()-1);
		}
	}





	/****************************************/


	//エージェントの数だけループ
	for (int agentsnum = 0; agentsnum < ourAgentsS; agentsnum++) {
		

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
void  Prefetching::calculatePrefetching(vector<vector<pair<int, int>>>route, vector<pair<int, int>> beforeAgentPosition,
	vector<vector<int>>moveUpTile, int readTurn)
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
	vector<vector<vector<vector<int>>>> turnMovedTileAgent(useReadTurn,vector<vector<vector<int>>>(map->width,vector<vector<int>>(map->vertical)));
	//x->y->visitedAgentCounter
	//push_backで追加
	vector<vector<int>> movedTiledCounter(map->width,vector<int>(map->vertical));
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

	// 重複判定完了
	
	//agentfield作成しようか

	//ここからややこしくなる






}
#include"Prefetching.h"
#include"Evalution.h"
#include"../Data/AgentsEvalution.h"


void Prefetching::prefetching()
{
	int dx[9] = { 1,1,1,0,0,0,-1,-1,-1 };
	int dy[9] = { 1,0,-1,1,0,-1,1,0,-1 };

	//����ꂽ�^�[���̒��łǂ�����čō��]���_���o����

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
	// route �̒�`
	vector<vector<pair<int, int>>>route(agents->ourAgents.size());
	
	// 3��̃r�[���T�[�`���
	vector<vector<pair<int, int>>>fork(agents->ourAgents.size());
	

	// agentsEvalution��turnTiledField�̏�����
	agentsEvalution->turnTiledField.resize(map->width,vector<int>(map->vertical));
	agentsEvalution->turnTiledField = field->tiled;
	



	//�ŏ���3�������
	rep(num, agents->ourAgents.size()) {

		priority_queue<pair<float, pair<int, int>>> Pqueue;
		
		rep(counter, 9) {

			int nowX = agents->ourAgents[num][1] + dx[counter];
			int nowY = agents->ourAgents[num][2] + dy[counter];

			// �͈͊O�v�Z
			if (nowX >= map->width || nowX < 0 || nowY >= map->vertical || nowY < 0) {
				Pqueue.push(make_pair(mINF,make_pair(dx[counter],dy[counter])));
			}
			// evalutionField�̒l����
			else {
				float evalutionP = evalution.calculateEvalutionPoint(nowX, nowY);
				Pqueue.push(make_pair(evalutionP, make_pair(dx[counter], dy[counter])));
			}
		}
		//���3���I��
		rep(tmp, 3) {
			fork[num].push_back(Pqueue.top().second);
			Pqueue.pop();
		}
	}





	//maxRoute,actionDXDY�̏�����
	agentsEvalution->maxRoute.resize(0);
	agentsEvalution->maxRoute.resize(agents->ourAgents.size(), vector<pair<int, pair<int, int>>>(0));
	

	agentsAction->actionType.resize(0);
	agentsAction->actionType.resize(agents->ourAgents.size());




	// moveUpTile�̒�`
	vector<vector<int>> moveUpTile(map->width,vector<int>(map->vertical));
	rep(i, map->width) {
		rep(j, map->vertical) {
			moveUpTile[i][j] = field->tiled[i][j];
		}
	}

	/******************�V�K�L��****************/

	// agent�̌��݈ʒu calculatePrefetching�Ŏg��
	vector<pair<int, int>> beforeAgentsPosition;
	rep(num, agents->ourAgents.size()) {
		beforeAgentsPosition.push_back(make_pair(agents->ourAgents[num][1], agents->ourAgents[num][2]));
	}


	rep(num, agents->ourAgents.size()) {
		rep(FORK, fork[num].size()) {

			//�T�C�Y�� +1
			route[num].push_back(fork[num][FORK]);
			
			// �v�Z
			calculatePrefetching(route, beforeAgentsPosition, moveUpTile, map->readTurn-1);

			// �T�C�Y�� -1
			route[num].resize(route[num].size()-1);
		}
	}





	/****************************************/


	//�G�[�W�F���g�̐��������[�v
	for (int agentsnum = 0; agentsnum < ourAgentsS; agentsnum++) {
		

		//agentsEvalution��max�]���l��������
		agentsEvalution->maxEvalutionPoint = mINF;


		//���ԖڂɌv�Z
		calculateEvalution(route, agentPosition, moveUpTile, agentsnum, map->readTurn, 0);

		route.resize(0);


		/*�����܂Ō���*/
		/////////////////////////////////////////////////////////
		//AgentsAction.h�ɏ�������
		agentsAction->actionDxDy[agentsnum].resize(0);
		agentsEvalution->maxEvalutionPoint = mINF;

	}

	//�@�ړ���d���m�F
	changeDestination();
	

	//�ړ��挈�� and ��������
	for(int agentsnum=0;agentsnum<ourAgentsS;agentsnum++){
		//
		int nowX = agents->ourAgents[agentsnum][1];
		int nowY = agents->otherAgents[agentsnum][2];

		rep(i, map->readTurn) {
			// ���������Position
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
				// moveUpTile�ɍX�V
				// ��̃^�[���̃^�C���ɂ����f
				for (int tmp = i; i < map->readTurn; i++) {
					moveUpTile[tmp + 1][nowX][nowY] = 0;
				}
				
				nowX -= agentsEvalution->maxRoute[agentsnum][i].second.first;
				nowY -= agentsEvalution->maxRoute[agentsnum][i].second.second;
			}
			else {
				//move	
				// moveUpTile�ɍX�V
				// ��̃^�[���̃^�C���ɂ����f
				for (int tmp = i; i < map->readTurn; i++) {
					moveUpTile[tmp + 1][nowX][nowY] = map->ourTeamID;
				}
				agentsAction->actionType[agentsnum].push_back(1);

			}
		}
	}





}



//�o�H�v�Z
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


			//��ʊO
		if (Dx + dx[turn] < 0 || Dx + dx[turn] >= map->width || Dy + dy[turn] < 0 || Dy + dy[turn] >= map->vertical) {
			goto fini;
		}

		//�߂낤�Ƃ���Ƃ��̏��O
		//dx,dy�������Ă�Ƃ�

		//�ړ��悪�����`�[���i�߂���܂܂��j
		if (moveUpTile[map->readTurn-readTurn][Dx + dx[turn]][Dy + dy[turn]] == map->ourTeamID) {
			// sum �����炷����
		}
		//�ړ��悪����`�[���^�C����������
		else if (moveUpTile[map->readTurn-readTurn][Dx + dx[turn]][Dy + dy[turn]] == map->otherTeamID) {

			moveUpTile[map->readTurn-readTurn][Dx + dx[turn]][Dy + dy[turn]] = 0;
			Dx -= dx[turn];
			Dy -= dy[turn];

		}
		else {
			// tile	��h��	
			moveUpTile[map->readTurn-readTurn][Dx + dx[turn]][Dy + dy[turn]] = map->ourTeamID;

		}


		//�ʒu�X�V
		Dx += dx[turn];
		Dy += dy[turn];

		//��ǂ݃^�[����(readTurn)���ċA�ŌĂяo�����т�-1
		if (readTurn > 1) {
			route.push_back(make_pair(route[0].first, make_pair(dx[turn], dy[turn])));
			giveReadTurn = readTurn - 1;


			calculateEvalution(route, make_pair(Dx, Dy), moveUpTile, agentsnum, giveReadTurn, sum);
			route.resize(route.size() - 1);

		}
		else if (readTurn == 1) {
			route.push_back(make_pair(route[0].first, make_pair(dx[turn], dy[turn])));

			//�]���v�Z
			evalution.calculateEvalution(route, moveUpTile, agentsnum, sum);
			route.resize(route.size() - 1);
		}


		//route.resize(route.size() - 1);
		//routeSize�̂��߂ɃG�[�W�F���g�̈ʒu���͈͊O�ł�push���Ă���łȂ���null�Q�Ƃ��N��������A
		//push_back���ׂ�

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
	
	// defalut�͌���4�^�[���ݒ�
	int useReadTurn = map->maxLimitReadTurn;
	// �͈͊O�A�N�Z�X�̃G���[��h��
	if (map->readTurn < map->maxLimitReadTurn) {
		useReadTurn = map->readTurn;
	}

	//turn->x->y->visitedAgentCounter
	vector<vector<vector<vector<int>>>> turnMovedTileAgent(useReadTurn,vector<vector<vector<int>>>(map->width,vector<vector<int>>(map->vertical)));
	//x->y->visitedAgentCounter
	//push_back�Œǉ�
	vector<vector<int>> movedTiledCounter(map->width,vector<int>(map->vertical));
	// turn->x->y
	vector<vector<vector<int>>> turnTiled(useReadTurn + 1, vector<vector<int>>(map->width, vector<int>(map->vertical)));


	rep(turn, useReadTurn) {
		turnTiled[turn] = field->tiled;
	}


	// 2�񓯂��y�A���v�Z���Ȃ��悤�ɏd��������s��
	rep(main, agents->ourAgents.size() - 1) {
		for (int partner = main + 1; partner < agents->ourAgents.size; partner++) {
			
			mainAgent = make_pair(agents->ourAgents[main][1], agents->ourAgents[main][2]);
			partnerAgent = make_pair(agents->ourAgents[partner][1], agents->ourAgents[partner][2]);

			//���ׂ�@��ǂ݃^�[�� 1 ~ readTurn
			//��ǂ݃^�[������傫������������u�܂����v���炢����������4�ɂ���
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
					// ����^�C����������̌v�Z
					if (turnTiled[turn][mainAgent.first][mainAgent.second] == map->otherTeamID) {
						for (int turnCount = turn; turnCount < useReadTurn - 1; turnCount++) {
							//	���̃^�[���̃t�B�[���h�ɍX�V
							turnTiled[turn + 1][mainAgent.first][mainAgent.second] = 0;
						}
						// �^�C�������ł̓G�[�W�F���g�̈ʒu�͓����Ȃ�
						mainAgent.first -= agentsEvalution->maxRoute[main][turn].second.first;
						mainAgent.second -= agentsEvalution->maxRoute[main][turn].second.second;
					}
					if (turnTiled[turn][partnerAgent.first][partnerAgent.second] == map->otherTeamID) {
						for (int turnCount = turn; turnCount < useReadTurn - 1; turnCount++) {
							//	���̃^�[���̃t�B�[���h�ɍX�V
							turnTiled[turn + 1][partnerAgent.first][partnerAgent.second] = 0;
						}
							// �^�C�������ł̓G�[�W�F���g�̈ʒu�͓����Ȃ�
						partnerAgent.first -= agentsEvalution->maxRoute[partner][turn].second.first;
						partnerAgent.second -= agentsEvalution->maxRoute[partner][turn].second.second;
					}



				}
			}
		}
	}

	// �d�����芮��
	
	//agentfield�쐬���悤��

	//���������₱�����Ȃ�






}
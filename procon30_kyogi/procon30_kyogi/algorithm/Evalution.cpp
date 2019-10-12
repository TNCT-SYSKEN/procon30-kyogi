#include"Evalution.h"


float evalution[] = { 6,5,4,3,4.3 ,4};
// 0. �̈�, ����̓_��������, �ړ��\�}�X,�@�ړ���̓_���̍���,�^�C������,�O���ɍs�����Ƃ��Ă��邩, 6. Analysis


float magnificat[] = { 1.1 , 1.2,1,1,1,1 };
/*
	�{���␳
	0 �^�C����������Ƃ��@tilePoint��������i�����߁j
	1 ����̗̈�|�C���g�������̂��̂�荂���Ƃ�
	2 ����̂ق����|�C���g������

*/

void Evalution::calculateEvalution(vector<pair<int, pair<int, int>>> route, vector<vector<int>>moveUpTile, int agentsnum, int sum)
{

	int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
	int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };


	Map *map;
	map = map->getMap();
	AgentsEvalution* agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();
	Field *field;
	field = field->getField();
	Agents* agents;
	agents = agents->getAgents();
	AgentsAction* agentsAction;
	agentsAction = agentsAction->getAgentsAction();


	//�G�[�W�F���g�����̃}�X�̕t�߂ɂ�����]����������i��ǎ���ł͏グ��j
	//���肪�^�C���|�C���g�ȏ�̓_���������̈����������̂Ƃ݂Ȃ��A
	//�|�C���g���傫����Α傫���قǕ]���_�̏オ�蒲�q���傫������

	//�����̃`�[����tiled�𓥂����Ƃ���Ƃ��ɂ͕]���_���߂��ቺ����
	//�������͕]�����Ȃ�

	//�]���_���v
	float sumOfEvalution = 0;

	//�v�Z�r���ł̃G�[�W�F���g�̓��������position
	int nowX = route[0].second.first;
	int nowY = route[0].second.second;
	
	vector<vector<int>>tiledArea;
	tiledArea.resize(map->width, vector<int>(map->vertical));

	

	nowX = route[0].second.first;
	nowY = route[0].second.second;

	//�^�C���X�R�A�v�Z
	rep(turn, map->readTurn) {
		nowX += route[turn+1].second.first;
		nowY += route[turn+1].second.second;

		Prefetching Pre;
		int calcTurn = 0;
		//���������Ȃ���
		if (route[turn + 1].second.first == 0 && route[turn + 1].second.second==0) {
			calcTurn = 4;
		}
		
		if (map->AnalysFieled == true) {
			sumOfEvalution += field->AnalysisField[nowX][nowY] * evalution[6];
		}

	
		//�[�ɍs���قǕ]���_�͍����Ȃ�
		sumOfEvalution += (abs(nowX - map->width/2) + abs(nowY - map->vertical/2) )* evalution[5];

		//�^�C���|�C���g�v�Z
		//����^�C�������̏ꍇ
		if (field->tiled[nowX][nowY] == map->otherTeamID) {
			
			sumOfEvalution += field->points[nowX][nowY] * magnificat[0];
			sumOfEvalution += map->score[1][2] * magnificat[1];

			//�ʒu��߂�
			nowX -= route[turn + 1].second.first;
			nowY -= route[turn + 1].second.second;
		}
		else {
			//�^�C���X�R�A���Z
			sum += Pre.calculateScore(make_pair(nowX, nowY),calcTurn);
		}
		
	}


	nowX = route[0].second.first;
	nowY = route[0].second.second;

	
	
	int lastGetEnemyAreaPointR = map->score[1][2];
	//�G�^�C���������s�����ǂ���
	//if (map->calcArea){
	//	rep(i, map->readTurn) {

	//		nowX += route[i + 1].second.first;
	//		nowY += route[i + 1].second.second;

	//		if (field->tiled[nowX][nowY] == map->otherTeamID) {

	//			int areaenemypoint = map->score[0][2] - calculateEnemyAreaPoint(route);

	//				/////////////////////////////////////////////////////
	//				if (areaenemypoint > 0) {

	//					sumOfEvalution += (float)(areaenemypoint*evalution[0]);
	//				}

	//		}

	//	}
	//}


	//�����`�[���̈���邩�ǂ����̌v�Z
	//GUIToggleSwitch�Ő؂�ւ���Ώ�
	if (map->calcArea) {
		sum += calculateAreaPoint(moveUpTile);
	}
	
	

	//����������
	///////////////////////////////////////////////
	nowX = route[0].second.first;
	nowY = route[0].second.second;
	
	
	
	rep(count, agentsnum) {
		int OnowX = agents->ourAgents[count][1];
		int OnowY = agents->ourAgents[count][2];



		rep(turn, map->readTurn) {

			OnowX += agentsAction->actionDxDy[count][turn].second.first;
			OnowY += agentsAction->actionDxDy[count][turn].second.second;

			nowX += route[turn + 1].second.first;
			nowY += route[turn + 1].second.second;


			sumOfEvalution -= 3 - abs(OnowX - nowX)*1.3;
		}
	}





	/*  �ړ��\�}�X�v�Z	*/

	rep(i, map->width) {
		rep(j, map->vertical) {
			tiledArea[i][j] = field->tiled[i][j];
		}
	}

	//�G�[�W�F���g�񐔃��[�v

	int agentsSize = agents->ourAgents.size();
	rep(i, agentsSize) {
		if (route[0].first != agents->ourAgents[i][0]) {
			//�����@-2
			tiledArea[agents->ourAgents[i][1]-1][agents->ourAgents[i][2]-1] = -2;
		}
		//�G�@-3
		tiledArea[agents->otherAgents[i][1]-1][agents->otherAgents[i][2]-1] = -3;
		
	}

	nowX = route[0].second.first;
	nowY = route[0].second.second;
	//�ړ��\�}�X
	int canMove = 0;
	rep(i, map->readTurn) {

		nowX += route[i+1].second.first;
		nowY += route[i+1].second.second;

		//�X����
		rep(j, 9) {
			//�}�X�����ƂłȂ��Ȃ��
			if (nowX + dx[j] >=0 && nowX + dx[j] < map->width
				&& nowY + dy[j] >= 0 && nowY + dy[j] < map->vertical) {
				if (tiledArea[nowX + dx[j]][nowY + dy[j]] == map->ourTeamID) {
				}
				else if(tiledArea[nowX+dx[j]][nowY+dy[j]]==map->otherTeamID){
					canMove --;
				}
				canMove++;
			}
		}
		
		//sumOfEvalution += canMove* evalution[2];
	}
	
	//�ړ��\�}�X�]�����Z

	

	if (map->score[0][0] < map->score[1][0]) {
		sumOfEvalution += sum * evalution[3] * magnificat[2];
	}
	else {
		sumOfEvalution += sum * evalution[3];
	}
	
	/*	///////////////////////////////////	*/

	




	int routeS = map->readTurn;
	//Route�X�V�i�]���ő�j

	
	if (agentsEvalution->maxEvalutionPoint < sumOfEvalution) {


		//map->score[1][2]++;
		agentsEvalution->maxEvalutionPoint = sumOfEvalution;

		agentsEvalution->maxRoute[agentsnum].resize(0);
		rep(i, routeS) {
			agentsEvalution->maxRoute[agentsnum].push_back(route[i+1]);
			
			
		}
		
	}
	


}











//�̈�|�C���g�v�Z
int Evalution::calculateAreaPoint(vector<vector<int>> moveUpTile) {
	Field *field;
	field = field->getField();

	Map *map;
	map = map->getMap();


	//����̗̈�|�C���g
	int lastAreaPoint = 0;




	vector<vector<int>> tiledArea;
	tiledArea.resize(map->width + 2, vector<int>(map->vertical + 2));
	vector<pair<int, int>>lastMove(1);

	int ddx[4] = { 1,-1,0,0 };
	int ddy[4] = { 0,0,1,-1 };
	int lastSize = 1;
	//��ǂ݂̐��������[�v
	//������
	rep(i, map->width + 2) {
		rep(j, map->vertical + 2) {
			tiledArea[i][j] = 0;
		}
	}

	rep(i, map->width) {
		rep(j, map->vertical) {
			if (field->tiled[i][j] == map->ourTeamID)
			{
				tiledArea[i + 1][j + 1] = map->ourTeamID;
			}

		}
	}


	lastMove[0] = make_pair(0, 0);

	
	tiledArea[0][0] = -1;
	lastSize = 1;

	//lastMove���X�V�������ɂ����ɏ������������Ȃ�
	vector<pair<int, int>>stac;


	while (1) {
		//�E�o
		if (lastSize == 0) {
			goto calc;
		}
		int counter = 0;

		rep(i, lastSize) {
			rep(k, 4) {
				if (lastMove[i].first + ddx[k] <= map->width + 1 &&
					lastMove[i].first + ddx[k] >= 0 &&
					lastMove[i].second + ddy[k] <= map->vertical + 1 &&
					lastMove[i].second + ddy[k] >= 0) {


					if (tiledArea[lastMove[i].first + ddx[k]][lastMove[i].second + ddy[k]] == 0) {
						tiledArea[lastMove[i].first + ddx[k]][lastMove[i].second + ddy[k]] = -1;

						stac.push_back(make_pair(lastMove[i].first + ddx[k], lastMove[i].second + ddy[k]));
						//stac[counter].first = lastMove[i].first + ddx[k];
						//stac[counter].second = lastMove[i].second + ddy[k];
						counter++;

					}
				}
			}
		}
		//�㏑��
		if (counter == 0) { goto calc; }
		lastMove.resize(counter);
		lastMove = stac;

		lastSize = counter;
		stac.resize(0);
	}

calc:;


	//�̈�v�Z
	rep(i, map->width) {
		rep(j, map->vertical) {
			if (tiledArea[i + 1][j + 1] == 0) {

				lastAreaPoint += abs(field->points[i][j]);

			}

		}
	}
	lastAreaPoint -= map->score[0][2];

	return lastAreaPoint;
}





//�G�^�C�������������̓G�̈�|�C���g�̕ω�
int Evalution::calculateEnemyAreaPoint(vector<pair<int, pair<int, int>>>route) {
	Field *field;
	field = field->getField();

	Map *map;
	map = map->getMap();


	//int nowX = route[0].second.first;
	//int nowY = route[0].second.second;



	//����̗̈�|�C���g
	int lastAreaPoint = 0;




	vector<vector<int>> tiledArea;
	tiledArea.resize(map->width+2, vector<int>(map->vertical+2));
	vector<pair<int, int>>lastMove(1);

	int ddx[4] = { 1,-1,0,0 };
	int ddy[4] = { 0,0,1,-1 };
	int lastSize = 1;
	//��ǂ݂̐��������[�v
	rep(count, map->readTurn) {
		//������
		rep(i, map->width + 2) {
			rep(j, map->vertical + 2) {
				tiledArea[i][j] = 0;
			}
		}

		rep(i, map->width) {
			rep(j, map->vertical) {
				if (field->tiled[i][j] == map->otherTeamID)
				{
					tiledArea[i + 1][j + 1] =map-> otherTeamID;
				}

			}
		}


		lastMove[0] = make_pair(0, 0);

		tiledArea[0][0] = -1;
		lastSize = 1;

		//lastMove���X�V�������ɂ����ɏ������������Ȃ�
		vector<pair<int, int>>stac;


		while (1) {
			//�E�o
			if (lastSize == 0) {
				goto calc;
			}
			int counter = 0;

			rep(i, lastSize) {
				rep(k, 4) {
					if (lastMove[i].first + ddx[k] <= map->width + 1 &&
						lastMove[i].first + ddx[k] >=0 &&
						lastMove[i].second + ddy[k] <= map->vertical + 1 &&
						lastMove[i].second + ddy[k]>=0) {


						if (tiledArea[lastMove[i].first + ddx[k]][lastMove[i].second + ddy[k]] == 0) {
							tiledArea[lastMove[i].first + ddx[k]][lastMove[i].second + ddy[k]] = -1;

							stac.push_back(make_pair(lastMove[i].first + ddx[k], lastMove[i].second + ddy[k]));
							//stac[counter].first = lastMove[i].first + ddx[k];
							//stac[counter].second = lastMove[i].second + ddy[k];
							counter++;
							
						}
					}
				}
			}
			//�㏑��
			if (counter == 0) { goto calc; }
			lastMove.resize(counter);
			lastMove = stac;

			lastSize = counter;
			stac.resize(0);

		}



	calc:;




	}
	//�̈�v�Z
	rep(i, map->width) {
		rep(j, map->vertical) {
			if (tiledArea[i + 1][j + 1] == 0) {
			
				lastAreaPoint += abs(field->points[i][j]);
				
			}

		}
	}
	//lastAreaPoint -= map->score[1][2] * map->readTurn;

	return lastAreaPoint;
}
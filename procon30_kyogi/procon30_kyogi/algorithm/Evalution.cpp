#include"Evalution.h"


float evalution[] = { 6,5,1.8,3,2.3 ,4 };
// 0. �̈�, ����̓_��������, �ړ��\�}�X,�@�ړ���̓_���̍���,�^�C������,�O���ɍs�����Ƃ��Ă��邩, 6. Analysis


float magnificat[] = { 1.1 , 1.2,1,1,1,1 };
/*
	�{���␳
	0 �^�C����������Ƃ��@tilePoint��������i�����߁j
	1 ����̗̈�|�C���g�������̂��̂�荂���Ƃ�
	2 ����̂ق����|�C���g������

*/

void Evalution::calculateEvalution(vector<pair<int, pair<int, int>>> route, vector<vector<vector<int>>>moveUpTile, int agentsnum, int sum)
{

	Map *map;
	map = map->getMap();
	AgentsEvalution* agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();
	


	//�G�[�W�F���g�����̃}�X�̕t�߂ɂ�����]����������i��ǎ���ł͏グ��j
	//���肪�^�C���|�C���g�ȏ�̓_���������̈����������̂Ƃ݂Ȃ��A
	//�|�C���g���傫����Α傫���قǕ]���_�̏オ�蒲�q���傫������

	// �� �]���𕁒ʂ��炢�ɂ���
	//�����̃`�[����tiled�𓥂����Ƃ���Ƃ��ɂ͕]���_���߂��ቺ����
	//�������͕]�����Ȃ�

	int routeS = map->readTurn;
	//Route�X�V�i�]���ő�j


	if (agentsEvalution->maxEvalutionPoint < sumOfEvalution) {

		//map->score[1][2]++;
		agentsEvalution->maxEvalutionPoint = sumOfEvalution;

		agentsEvalution->maxRoute[agentsnum].resize(0);
		rep(i, routeS) {
			// �����ʒu�͒ǉ����Ȃ�
			agentsEvalution->maxRoute[agentsnum].push_back(route[i + 1]);
		}
	}

}



// �t�B�[���h�]��point�v�Z
void Evalution::calculateEvalutionPoint()
{
	int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
	int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };

	Map *map;
	map = map->getMap();
	Field *field;
	field = field->getField();
	Agents* agents;
	agents = agents->getAgents();


	/*  �ړ��\�}�X�v�Z	*/
	vector<vector<int>>agentsPositionField(map->width, vector<int>(map->vertical,0));

	//�G�[�W�F���g�񐔃��[�v
	int agentsSize = agents->ourAgents.size();
	rep(i, agentsSize) {
		//�����@-2
		agentsPositionField[agents->ourAgents[i][1]][agents->ourAgents[i][2]] = -2;
		
		//�G�@-3
		agentsPositionField[agents->otherAgents[i][1]][agents->otherAgents[i][2]] = -3;

	}
	//�ړ��\�}�X
	float canMove = 0;



	rep(i, map->width) {
		rep(j, map->vertical) {
			
			

			// Analys POINT
			if (map->AnalysField == true) {
				field->evalutionField[i][j] += field->AnalysisField[i][j] * evalution[6];
			}

			//����^�C�������̏ꍇ
			if (field->tiled[i][j] == map->otherTeamID) {

				field->evalutionField[i][j] += field->points[i][j]* evalution[4] * magnificat[0];
				
			}
			// ���`�[���^�C���̏ꍇ
			else if (field->tiled[i][j] == map->ourTeamID) {
				field->evalutionField[i][j] += 0;
			}
			else {

				// �����荂�����ǂ����ŕ]���ɔ{���␳��������
				if (map->score[0][0] < map->score[1][0]) {
					// tile POINT
					field->evalutionField[i][j] = field->points[i][j] * evalution[3] * magnificat[2];
				}
				else {
					// tile POINT
					field->evalutionField[i][j] = field->points[i][j] * evalution[3];
				}
			}

			//�[�ɍs���قǕ]���_�͍����Ȃ�
			field->evalutionField[i][j] += (abs(i - map->width / 2) + abs(j - map->vertical / 2))* evalution[5];
		
			// �ړ��\�}�X�v�Z
			//�X����
			rep(count, 9) {
				//�}�X�����ƂłȂ��Ȃ��
				int newX = i + dx[count];
				int newY = j + dy[count];

				if (newX >= 0 && newX < map->width
					&& newY >= 0 && newY < map->vertical) {

					if (agentsPositionField[newX][newY] == -2 || field->tiled[newX][newY]== map->ourTeamID) {
						
						// �G�[�W�F���g�Ȃ�
						if (agentsPositionField[newX][newY] == -2) {
							canMove += 0;
						}
						else {
							canMove++;
						}
					}
					else if (agentsPositionField[newX][newY] ==-3 || field->tiled[newX][newY] == map->otherTeamID) {
						canMove += 0.5;
					}
					else {
						canMove++;
					}
				}
			}
		
		}
	}
	
	

	
}









//�̈�v�Z�̕���
/*

//�̈�|�C���g�v�Z
int Evalution::calculateAreaPoint(vector<vector<int>> moveUpTile) {
	Field *field;
	field = field->getField();

	Map *map;
	map = map->getMap();


	//����̗̈�|�C���g
	int lastAreaPoint = 0;




	vector<vector<int>> agentsPositionField;
	agentsPositionField.resize(map->width + 2, vector<int>(map->vertical + 2));
	vector<pair<int, int>>lastMove(1);

	int ddx[4] = { 1,-1,0,0 };
	int ddy[4] = { 0,0,1,-1 };
	int lastSize = 1;
	//��ǂ݂̐��������[�v
	//������
	rep(i, map->width + 2) {
		rep(j, map->vertical + 2) {
			agentsPositionField[i][j] = 0;
		}
	}

	rep(i, map->width) {
		rep(j, map->vertical) {
			if (field->tiled[i][j] == map->ourTeamID)
			{
				agentsPositionField[i + 1][j + 1] = map->ourTeamID;
			}

		}
	}


	lastMove[0] = make_pair(0, 0);


	agentsPositionField[0][0] = -1;
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


					if (agentsPositionField[lastMove[i].first + ddx[k]][lastMove[i].second + ddy[k]] == 0) {
						agentsPositionField[lastMove[i].first + ddx[k]][lastMove[i].second + ddy[k]] = -1;

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
			if (agentsPositionField[i + 1][j + 1] == 0) {

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




	vector<vector<int>> agentsPositionField;
	agentsPositionField.resize(map->width + 2, vector<int>(map->vertical + 2));
	vector<pair<int, int>>lastMove(1);

	int ddx[4] = { 1,-1,0,0 };
	int ddy[4] = { 0,0,1,-1 };
	int lastSize = 1;
	//��ǂ݂̐��������[�v
	rep(count, map->readTurn) {
		//������
		rep(i, map->width + 2) {
			rep(j, map->vertical + 2) {
				agentsPositionField[i][j] = 0;
			}
		}

		rep(i, map->width) {
			rep(j, map->vertical) {
				if (field->tiled[i][j] == map->otherTeamID)
				{
					agentsPositionField[i + 1][j + 1] = map->otherTeamID;
				}

			}
		}


		lastMove[0] = make_pair(0, 0);

		agentsPositionField[0][0] = -1;
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


						if (agentsPositionField[lastMove[i].first + ddx[k]][lastMove[i].second + ddy[k]] == 0) {
							agentsPositionField[lastMove[i].first + ddx[k]][lastMove[i].second + ddy[k]] = -1;

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
			if (agentsPositionField[i + 1][j + 1] == 0) {

				lastAreaPoint += abs(field->points[i][j]);

			}

		}
	}
	//lastAreaPoint -= map->score[1][2] * map->readTurn;

	return lastAreaPoint;
}

*/
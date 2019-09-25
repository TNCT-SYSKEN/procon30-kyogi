#include"Evalution.h"


float evalution[4] = { 3,4,5,6, };
// �̈�, ����̓_��������, �ړ��\�}�X,�@�ړ���̓_���̍���


void Evalution::calculateEvalution(vector<pair<int, pair<int, int>>> route, int sum)
{

	Map *map;
	map = map->getMap();
	AgentsEvalution* agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();
	Field *field;
	field = field->getField();



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
	//�G�^�C���������s�����ǂ���
	rep(i, map->readTurn) {
		nowX+=route[i+1].second.first;
		nowY += route[i+1].second.second;
		if (field->tiled[nowX][nowY] == map->otherTeamID) {

			int areaEnemyPoint = calculateEnemyAreaPoint(route);
			/////////////////////////////////////////////////////
			sumOfEvalution += (float)(areaEnemyPoint*evalution[0]);
			
			goto KUSA;
		}
	}
	KUSA:;

	rep(i, map->readTurn) {



		//(�����_)�����̃X�R�A < ����̃X�R�A
		if (map->score[0][0] < map->score[1][0]) {
			sumOfEvalution += evalution[2];
		}

		

	}

	int routeS = route.size() - 1;
	//Route�X�V�i�]���ő�j
	if (agentsEvalution->maxEvalutionPoint < sumOfEvalution) {
		
		rep(i, routeS) {
			agentsEvalution->maxRoute[i] = route[i + 1].second;
		}
		
	}
	

}

//�̈�|�C���g�v�Z
int Evalution::calculateAreaPoint(vector<pair<int,pair<int,int>>>route) {
	Field *field;
	field = field->getField();

	Map *map;
	map = map->getMap();


	int nowX = route[0].second.first;
	int nowY = route[0].second.second;
	//�̈�`�F�b�N������
	bool IF = false;

	//����̗̈�|�C���g
	int lastAreaPoint = 0;


	pair<int,int> lastPos;


	vector<vector<int>>tiledArea;
	//������
	rep(i, map->width) {
		rep(j, map->vertical) {
			if (field->tiled[i][j]==0)
			{
				tiledArea[i][j] = 0;
			}
			else if(field->tiled[i][j]==map->ourTeamID)
			{
				tiledArea[i][j] = 1;
			}
		}
	}
	

	//��ǂ݂̐��������[�v
	rep(count, map->readTurn) {
		nowX += route[count + 1].second.first;
		nowY += route[count + 1].second.second;


		tiledArea[nowX][nowY] = 1;



		//width ��
		rep(i, map->width) {
			IF = false;

			//verticala �c
			rep(j, map->vertical) {
				if (tiledArea[i][j]==1) {
					if (IF) {

						//
						for (int last = lastPos.second; last < j; last++) {
							tiledArea[i][last] = 5;
						}
					}
					else {
						IF = true;
						lastPos = make_pair(i, j);
					}
				}
				else {
					tiledArea[i][j] = 0;
				}
			}
		}

		//vertical �c
		rep(j, map->vertical) {
			IF = false;

			//width ��
			rep(i, map->width) {
				if (tiledArea[i][j] == 1) {
					if (IF) {

						//
						for (int last = lastPos.first+1; last < i; last++) {
							tiledArea[i][last] = 5;
						}
					}
					else {
						IF = true;
						lastPos = make_pair(i, j);
					}
				}
				else {
					tiledArea[i][j] = 0;
				}
			}
		}
		//�̈�v�Z
		rep(i, map->width) {
			rep(j, map->vertical) {
				if (tiledArea[i][j] == 5) {
					lastAreaPoint += field->points[i][j];
				}
			}
		}
		lastAreaPoint -= map->score[1][2];

	}

	return lastAreaPoint;
}

//�G�^�C�������������̓G�̈�|�C���g�̕ω�
int Evalution::calculateEnemyAreaPoint(vector<pair<int, pair<int, int>>>route) {
	Map *map;
	map = map->getMap();

	Field *field;
	field = field->getField();

	vector<vector<int>>enemyTiledArea;
	int nowX = route[0].second.first;
	int nowY = route[0].second.first;
	   

	bool IF = false;

	//����̗̈�|�C���g
	int lastAreaPoint = 0;

	pair<int, int> lastPos;



	//������
	rep(i, map->width) {
		rep(j, map->vertical) {
			if (field->tiled[i][j] == 0) {
				enemyTiledArea[i][j] = 0;

			}
			else if (field->tiled[i][j] == map->otherTeamID) {
				enemyTiledArea[i][j] = 1;

			}
		}
	}


	//��ǂ݂̐��������[�v
	rep(count, map->readTurn) {
		nowX += route[count + 1].second.first;
		nowY += route[count + 1].second.second;


		enemyTiledArea[nowX][nowY] = 1;



		//width ��
		rep(i, map->width) {
			IF = false;

			//verticala �c
			rep(j, map->vertical) {
				if (enemyTiledArea[i][j] == 1) {
					if (IF) {

						//
						for (int last = lastPos.second; last < j; last++) {
							enemyTiledArea[i][last] = 5;
						}
					}
					else {
						IF = true;
						lastPos = make_pair(i, j);
					}
				}
				else {
					enemyTiledArea[i][j] = 0;
				}
			}
		}

		//vertical �c
		rep(j, map->vertical) {
			IF = false;

			//width ��
			rep(i, map->width) {
				if (enemyTiledArea[i][j] == 1) {
					if (IF) {

						//
						for (int last = lastPos.first + 1; last < i; last++) {
							enemyTiledArea[i][last] = 5;
						}
					}
					else {
						IF = true;
						lastPos = make_pair(i, j);
					}
				}
				else {
					enemyTiledArea[i][j] = 0;
				}
			}
		}
		//�̈�v�Z
		rep(i, map->width) {
			rep(j, map->vertical) {
				if (enemyTiledArea[i][j] == 5) {
					lastAreaPoint += field->points[i][j];
				}
			}
		}
		lastAreaPoint -= map->score[0][2];

	}

	return lastAreaPoint;
}
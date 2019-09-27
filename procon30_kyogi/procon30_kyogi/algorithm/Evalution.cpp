#include"Evalution.h"

int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };

float evalution[4] = { 6,5,4,3, };
// �̈�, ����̓_��������, �ړ��\�}�X,�@�ړ���̓_���̍���


float magnificat[] = { 1,1.5,1,1,1,1 };
/*
	�{���␳
	0 �^�C����������Ƃ��@tilePoint��������i�����߁j
	1 ����̗̈�|�C���g�������̂��̂�荂���Ƃ�
	2 ����̂ق����|�C���g������

*/

void Evalution::calculateEvalution(vector<pair<int, pair<int, int>>> route, int sum)
{

	Map *map;
	map = map->getMap();
	AgentsEvalution* agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();
	Field *field;
	field = field->getField();
	Agents* agents;
	agents = agents->getAgents();



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
			if (areaEnemyPoint != 0) {

				sumOfEvalution += (float)(areaEnemyPoint*evalution[0]);
			}
			
			
			goto KUSA;
		}
	}
	KUSA:;

	//�ړ��\�}�X�v�Z
	vector<vector<int>>tiledArea;
	rep(i, map->width) {
		rep(j, map->width) {
			if (tiledArea[i][j] == map->ourTeamID) {
				//�����^�C�� �P
				tiledArea[i][j] = 1;
			}
			else if (tiledArea[i][j] == map->otherTeamID) {
				//����^�C�� 2
				tiledArea[i][j] = 2;
			}

			tiledArea[i][j] = field->tiled[i][j];
		}
	}

	//�G�[�W�F���g�񐔃��[�v
	rep(i, agents->ourAgents.size()) {
		if (route[0].first != agents->ourAgents[i][0]) {
			//�����@�R
			tiledArea[agents->ourAgents[i][1]][agents->ourAgents[i][2]] = 3;
		}
		//�G�@�T
		tiledArea[agents->otherAgents[i][1]][agents->otherAgents[i][2]] = 5;
		
	}

	nowX = route[0].second.first;
	nowY = route[0].second.second;
	//�ړ��\�}�X
	int canMove = 0;
	rep(i, map->readTurn) {

		//�X����
		rep(j, 9) {
			//�}�X�����ƂłȂ��Ȃ��
			if (!(nowX + dx[j] < 0 && nowX + dx[j] < map->width
				&& nowY + dy[j] < 0 && nowY + dy[j] >map->vertical)) {
				if (tiledArea[nowX + dx[j]][nowY + dy[j]] == 1) {
				}
				else if(tiledArea[nowX+dx[j]][nowY+dy[j]]==3){
					canMove -= 2;
				}
				canMove++;
			}
		}

	}
	//�ړ��\�}�X�]�����Z
	sumOfEvalution += canMove * evalution[2];
	

	if (map->score[0][0] > map->score[1][0]) {
		sumOfEvalution += sum * evalution[3] * magnificat[2];
	}
	else {
		sumOfEvalution += sum * evalution[3];
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


		if (enemyTiledArea[nowX][nowY]==1) {
			nowX -= route[count + 1].second.first;
			nowY -= route[count + 1].second.second;
		}

		enemyTiledArea[nowX][nowY] = 0;



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
		lastAreaPoint = map->score[0][2] - lastAreaPoint;

	}
	//�ŏI�I�ɂ͑���̗̈�|�C���g���ǂꂾ����ꂽ�����킩��
	return lastAreaPoint;
}
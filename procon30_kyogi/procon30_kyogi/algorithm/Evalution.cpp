#include"Evalution.h"


float evalution[4] = { 3,4,5,6, };
// �̈�, ����̓_��������, �ړ��\�}�X,�@�ړ���̓_���̍���


void Evalution::calculateEvalution(vector<pair<int, pair<int, int>>> route, int readTurn, int sum)
{

	Map *map;
	map = map->getMap();

	AgentsEvalution *agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();


	//�]���_���v
	float sumOfEvalution = 0;

	rep(i, readTurn) {

		//(�����_)�����̃X�R�A < ����̃X�R�A
		if (map->score[0][0] < map->score[1][0]) {
			sumOfEvalution += evalution[2];
		}

		

	}

}

//�̈�|�C���g�v�Z
int calculateAreaPoint() {
	Field *field;
	field = field->getField();

	Map *map;
	map = map->getMap();


	vector<vector<int>>tiledArea;
	//������
	rep(i, map->width) {
		rep(j, map->vertical) {
			if (field->tiled[i][j]==0)
			{
				tiledArea[i][j] = 0;
			}
			else if(field->tiled[i][j]==map->ourTeaMID)
			{
				tiledArea[i][j] = 1;
			}
		}
	}

	rep(i, map->width) {

	}

	
}

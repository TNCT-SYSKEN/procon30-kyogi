#include"Evalution.h"


float evalution[4] = { 3,4,5,6, };
// �̈�, ����̓_��������, �ړ��\�}�X,�@�ړ���̓_���̍���


void Evalution::calculateEvalution(vector<pair<int, pair<int, int>>> route, int sum)
{

	Map *map;
	map = map->getMap();
	AgentsEvalution *agentsEvalution;
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
			calculateEnemyAreaPoint(route);
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

}

//�̈�|�C���g�v�Z
int calculateAreaPoint(vector<pair<int,pair<int,int>>>route) {
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
	

	//��ǂ݂̐��������[�v
	rep(count, map->readTurn) {

		tiledArea=

		//width ��
		rep(i, map->width) {
			//verticala �c
			rep(j, map->vertical) {
				if()
			}
		}
	}

	
}

//�G�^�C�������������̓G�̈�|�C���g�̕ω�
int calculateEnemyAreaPoint(vector<pair<int, pair<int, int>>>route) {
	Map *map;
	map = map->getMap();

	Field *field;
	field = field->getField();

	vector<vector<int>>enemyTiledArea;




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

	//��ǂ݃^�[���̐��������[�v
	rep(count, map->readTurn) {
		if(route.second.)
	}


}
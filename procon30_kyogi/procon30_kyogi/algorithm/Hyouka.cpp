#include"Hyouka.h"


//�S�ẴG�[�W�F���g�ɂ��Ĉ�C�ɕ]���_�v�Z�������ق���
//�ꏊ�ύX�Ȃǂ����₷��

//�]���_�v�Z�ɕK�v�ȏ���
//�t�B�[���h���A�^�C���󋵁A�G�[�W�F���g�̈ʒu
//�����̃`�[���̓��_�A����̃`�[���̓��_
//���ꂼ��������Ƃ��Ĉ���

vector<vector<int>> Hyouka::hyoukaKeisan()
{
	Map *map;
	map = map->getMap();

	Hyouka::hyoukaPoint={};//�]���_������


	int hyouka_p;
	

	

	

	return vector<vector<int>>();
}

int Hyouka::calculateScore(int x,int y)
{
	Map *map;
	map = map->getMap();
	Field *field;
	field = field->getField();

	int sum = 0;

	if (x <= 0 || x > map->width || y <= 0 || y > map->vertical) {
		return -1;
	}
	else {
		field->points[x - 1][y - 1];
	}

	return sum;
}



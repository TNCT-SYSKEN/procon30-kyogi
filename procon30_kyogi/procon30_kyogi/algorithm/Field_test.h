#pragma once
#include"../general.h"

class Field_test {
public:

	//�����Ńt�B�[���h�����e�X�g�p�Œ�`

	int *width;
	int *height;
	//teamID
	int *my_teamID;
	int *other_teamID;

	//�|�C���g���
	static vector<vector<int>>points;

	



	//�G�[�W�F���gID,x,y
	static vector<vector<int>>*agents;

	//�^�C����
	static vector<vector<int>>*tiled;

	//�^�C���|�C���g,�̈�|�C���g,���v�|�C���g
	//�����̃`�[��
	static vector<int>*my_team_point;

	//����̃`�[��
	static vector<int>*other_team_point;

	static void Field();
};



#pragma once
#include "../general.h"

class Map {
public:
	static Map* getMap();
	//�c
	int vertical;
	//��
	int width;



	Map(): score(2,vector<int>(3,0)){};

	
	//�����̃`�[���̃X�R�A{�����_,�^�C��,�̈�},
	//����				  {�����_,�^�C��,�̈�}
	vector<vector<int>> score;
	
	//�^�[����
	int turn = 0;

	//��ǂ݃^�[����
	int readTurn;

	//�ŏI�^�[����
	int finalTurn;

	//�����`�[��ID
	int ourTeamID;
	//����`�[��ID
	int otherTeamID;



	//�v�Z�������ǂ���
	bool turnFlg;
	bool isGameStarted;

private:
	static Map* stayMap;
};
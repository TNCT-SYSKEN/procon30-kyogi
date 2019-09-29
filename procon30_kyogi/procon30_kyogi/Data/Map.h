#pragma once
#include "../general.h"

class Map {
public:
	static Map* getMap();
	//�c
	int vertical;
	//��
	int width;

	//Map(): vSize(3,0) {};
	Map() : score(2, vector<int>(3,0)) {};
	//vector<int> vSize;
	//�����̃`�[���̃X�R�A{�����_,�^�C��,�̈�},
	//����				  {�����_,�^�C��,�̈�}
	vector<vector<int>> score;
	
	//�^�[����
	int turn = 0;

	int readTurn;

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
#pragma once
#include "../general.h"

class Map {
public:
	static Map* getMap();
	//�c
	int vertical;
	//��
	int width;

	//�����̃`�[���̃X�R�A{�����_,�^�C��,�̈�},
	//����				  {�����_,�^�C��,�̈�}
	vector<vector<int>> score;
	
	//�^�[����
	int turn;

	int readTurn = 3;

	//�����`�[��ID
	int ourTeamID;
	//����`�[��ID
	int otherTeamID;


private:
	static Map* stayMap;
};
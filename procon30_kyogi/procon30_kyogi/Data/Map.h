#pragma once
#include "../general.h"

class Map {
public:
	static Map* getMap();
	//��
	int width;

	//�c
	int vertical;

	
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

	//MapChange
	int mapChange=0;



	//�v�Z�������ǂ���
	bool turnFlg;
	bool isGameStarted;
	bool isSearchAll;
	bool makeReadTurnMap;
	//�ŏ���jsonfile �ǂݎ��
	bool firstJson=false;

private:
	static Map* stayMap;
};
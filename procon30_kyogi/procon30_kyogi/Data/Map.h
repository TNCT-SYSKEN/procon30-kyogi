#pragma once
#include "../general.h"

class Map {
public:
	static Map* getMap();
	//��
	int width;

	//�c
	int vertical;

	float startedAtUnixTime = 0;

	
	//�����̃`�[���̃X�R�A{�����_,�^�C��,�̈�},
	//����				  {�����_,�^�C��,�̈�}
	vector<vector<int>> score;
	
	//�^�[����
	int turn = 0;

	//��ǂ݃^�[����
	int readTurn;

	//�ŏI�^�[����
	int finalTurn=20;

	//�����`�[��ID
	int ourTeamID;
	//����`�[��ID
	int otherTeamID;

	//MapChange
	int mapChange=0;
	bool click;
	int x, y;



	//�v�Z�������ǂ���
	bool turnFlg=false;
	bool isGameStarted=false;
	bool isSearchAll=false;
	bool makeReadTurnMap=false;
	//�ŏ���jsonfile �ǂݎ��
	bool firstJson=false;
	//debug �����json���������ǂ�������
	bool enemyJson = false;
	
	//debugMode
	bool isDebug = true;
	//debug ���̃^�[���ɃG�[�W�F���g�̕]���v�Z�������ǂ���
	bool isCalcOurAction = false;

private:
	static Map* stayMap;
};
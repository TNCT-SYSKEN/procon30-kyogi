#pragma once
#include "../general.h"

class Map {
public:
	static Map* getMap();
	//��
	int width;

	//�c
	int vertical;

	//Unix����
	float startedAtUnixTime = 0;


	//�����̃`�[���̃X�R�A{�����_,�^�C��,�̈�},
	//����				  {�����_,�^�C��,�̈�}
	vector<vector<int>> score;

	//�^�[����
	int turn = 0;

	//��ǂ݃^�[����
	int readTurn;

	//�ŏI�^�[����
	int finalTurn = 20;

	//�����`�[��ID
	int ourTeamID;
	//����`�[��ID
	int otherTeamID;

	//TurnMap Change
	int mapChangeTurn = 0;
	bool isClicked;
	int clickedPosx, clickedPosy;

	//�̈�v�ZONOFF
	bool calcArea = false;


	//�v�Z�������ǂ���
	bool turnFlg = false;

	bool isSearchAll = false;
	bool makeReadTurnMap = false;
	//�ŏ���jsonfile �ǂݎ��
	bool firstJson = false;
	//debug �����json���������ǂ�������
	bool enemyJson = false;

	//debug ���̃^�[���ɃG�[�W�F���g�̕]���v�Z�������ǂ���
	bool isCalcOurAction = false;


	int makeJsonCount = 0;


	bool AnalysField = false;
	bool AnalysCalcC = false;


private:
	static Map* stayMap;
};
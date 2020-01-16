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

	//MapChange
	int mapChange = 0;
	bool click;
	int x, y;

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


	bool AnalysFieled = false;
	bool AnalysCalcC = false;


	string token = "dbc07e57a1e7b1342c0570d0a4393a53bef552ac2c900f3d2c21dd68a40f3d8b";
	string matchNumber;

private:
	static Map* stayMap;
};
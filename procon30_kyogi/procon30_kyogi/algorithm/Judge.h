#pragma once
#include"Action_manager.h"
#include"JudgeEvalution.h"

class Judge {
public:
	//�]���_�v�Z�ɕK�v�ȏ���
	//�t�B�[���h���A�^�C���󋵁A�G�[�W�F���g�̈ʒu
	//�����̃`�[���̓��_�A����̃`�[���̓��_
	//���ꂼ��������Ƃ��Ĉ���

	void fullSearch();



private:
	
	void calculateEnemyRoute(vector<pair<int, pair<int,int>>>,pair<int,int>,vector<pair<int,pair<int,int>>>,int ,int, int);
	void calculateAreaPoint(vector<pair<int, pair<int, int>>>, int,int);
	void calculateTilePoint(vector<pair<int, pair<int, int>>>, int);
	
};

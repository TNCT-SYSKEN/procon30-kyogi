#include"Hyouka.h"


//�S�ẴG�[�W�F���g�ɂ��Ĉ�C�ɕ]���_�v�Z�������ق���
//�ꏊ�ύX�Ȃǂ����₷��

//�]���_�v�Z�ɕK�v�ȏ���
//�t�B�[���h���A�^�C���󋵁A�G�[�W�F���g�̈ʒu
//�����̃`�[���̓��_�A����̃`�[���̓��_
//���ꂼ��������Ƃ��Ĉ���


vector<vector<>>route = {};//�o�H������

int dx[] = { 1,1,1,0,0,0,-1,-1,-1 };
int dy[] = { 1,0,-1,1,0,-1,1,0,-1 };
vector<vector<int>> Hyouka::hyoukaKeisan()
{
	Map *map;
	map = map->getMap();
	Agents* agents;
	agents = agents->getAgents();
	

	pair<int, int>agentPosition;
	
	

	 //�G�[�W�F���g�̐��������[�v
	for (int agentsnum = agents->ourAgents[0][0]; agentsnum < agents->ourAgents[0][agentsnum-1];agentsnum++) {
		
		agentPosition.first = agents->ourAgents[1][agentsnum-agents->ourAgents[0][0]];//x
		agentPosition.second = agents->ourAgents[2][agentsnum-agents->ourAgents[0][0]];//y

		calculateEvalution(agentsnum,agentPosition,map->readTurn,0);
	}

	

	

	return vector<vector<int>>();
}


//point�v�Z
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

//�o�H�v�Z
vector<int> Hyouka::calculateEvalution(int agentnum,pair<int,int>agentPosition,int readTurn,int turn)
{		
	Map* map;
	map = map->getMap();
	int toX, toY;
	
	rep(turn,9) {
		toX += dx[turn];
		toY += dy[turn];
		agentPosition.first
		calculateEvalution(agentnum,)
	}
	return vector<int>();
}


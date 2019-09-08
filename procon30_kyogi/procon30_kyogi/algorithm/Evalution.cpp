#include"Evalution.h"


float evalution[4] = { 3,4,5,6, };
// 領域, 相手の点が高いか, 移動可能マス,　移動先の点数の高さ


void Evalution::calculateEvalution(vector<pair<int, pair<int, int>>> route, int readTurn, int sum)
{

	Map *map;
	map = map->getMap();

	AgentsEvalution *agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();


	//評価点合計
	float sumOfEvalution = 0;

	rep(i, readTurn) {

		//(総合点)自分のスコア < 相手のスコア
		if (map->score[0][0] < map->score[1][0]) {
			sumOfEvalution += evalution[2];
		}

		

	}

}

//領域ポイント計算
int calculateAreaPoint() {
	Field *field;
	field = field->getField();

	Map *map;
	map = map->getMap();


	vector<vector<int>>tiledArea;
	//初期化
	rep(i, map->width) {
		rep(j, map->vertical) {
			if (field->tiled[i][j]==0)
			{
				tiledArea[i][j] = 0;
			}
			else if(field->tiled[i][j]==map->ourTeaMID)
			{
				tiledArea[i][j] = 1;
			}
		}
	}

	rep(i, map->width) {

	}

	
}

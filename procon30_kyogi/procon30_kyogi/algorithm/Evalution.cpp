#include"Evalution.h"


float evalution[4] = { 3,4,5,6, };
// 領域, 相手の点が高いか, 移動可能マス,　移動先の点数の高さ


void Evalution::calculateEvalution(vector<pair<int, pair<int, int>>> route, int sum)
{

	Map *map;
	map = map->getMap();
	AgentsEvalution *agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();
	Field *field;
	field = field->getField();


	//エージェントがそのマスの付近にいたら評価を下げる（戦局次第では上げる）
	//相手がタイルポイント以上の点を取ったら領域を取ったものとみなし、
	//ポイントが大きければ大きいほど評価点の上がり調子も大きくする
	
	//自分のチームのtiledを踏もうとするときには評価点をめちゃ下げる
	//もしくは評価しない

	//評価点合計
	float sumOfEvalution = 0;


	//計算途中でのエージェントの動いた後のposition
	int nowX = route[0].second.first;
	int nowY = route[0].second.second;
	//敵タイル除去を行うかどうか
	rep(i, map->readTurn) {
		nowX+=route[i+1].second.first;
		nowY += route[i+1].second.second;
		if (field->tiled[nowX][nowY] == map->otherTeamID) {
			calculateEnemyAreaPoint(route);
			goto KUSA;
		}
	}
	KUSA:;

	rep(i, map->readTurn) {



		//(総合点)自分のスコア < 相手のスコア
		if (map->score[0][0] < map->score[1][0]) {
			sumOfEvalution += evalution[2];
		}

		

	}

}

//領域ポイント計算
int calculateAreaPoint(vector<pair<int,pair<int,int>>>route) {
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
	

	//先読みの数だけループ
	rep(count, map->readTurn) {

		tiledArea=

		//width 横
		rep(i, map->width) {
			//verticala 縦
			rep(j, map->vertical) {
				if()
			}
		}
	}

	
}

//敵タイル除去した時の敵領域ポイントの変化
int calculateEnemyAreaPoint(vector<pair<int, pair<int, int>>>route) {
	Map *map;
	map = map->getMap();

	Field *field;
	field = field->getField();

	vector<vector<int>>enemyTiledArea;




	//初期化
	rep(i, map->width) {
		rep(j, map->vertical) {
			if (field->tiled[i][j] == 0) {
				enemyTiledArea[i][j] = 0;

			}
			else if (field->tiled[i][j] == map->otherTeamID) {
				enemyTiledArea[i][j] = 1;
			}
		}
	}

	//先読みターンの数だけループ
	rep(count, map->readTurn) {
		if(route.second.)
	}


}
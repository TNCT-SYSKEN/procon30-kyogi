#include "Action_manager.h"//general.h, Field_test.h, Hyouka.h

//このファイルを実行することですべてのアルゴリズム処理を実行させる
//master的なファイル


//	1.評価計算
//	2.移動情報を表示


void Action_manager::Action()
{	

	//Hyouka.cppの関数を呼び出す
	//現在の得点などをちゃんと別のファイル、もしくは関数で取得する必要がある。


	Prefetching prefetching;

	AgentsEvalution *agentsEvalution;
	agentsEvalution = agentsEvalution->getAgentsEvalution();

	Judge judge;
	
	Map* map;
	map = map->getMap();

	//全探索モードでなかったら
	if (!map->isSearchAll) {
		prefetching.hyoukaKeisan();
	}
	else {
		judge.fullSearch();
	}

}

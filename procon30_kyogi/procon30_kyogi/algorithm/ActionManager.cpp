#include "ActionManager.h"//general.h, Field_test.h, Hyouka.h
#include "Prefetching.cpp"
//このファイルを実行することですべてのアルゴリズム処理を実行させる
//master的なファイル


//	1.評価計算
//	2.移動情報を表示


void ActionManager::Action(int)
{	
	//テスト用の定義（後で消す）
	Field_test fieldtest;
	fieldtest.fieldTest();

	//評価計算
	Prefetching prefetching;
	prefetching.hyoukaKeisan();
	//Hyouka hyouka;
	//hyouka.hyoukaKeisan();
	

}

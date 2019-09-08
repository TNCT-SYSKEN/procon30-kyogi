#include "Action_manager.h"//general.h, Field_test.h, Hyouka.h

//このファイルを実行することですべてのアルゴリズム処理を実行させる
//master的なファイル


//	1.評価計算
//	2.移動情報を表示


int Action_manager::Action(int)
{	
	Field_test FT;
	//Hyouka.cppの関数を呼び出す
	//現在の得点などをちゃんと別のファイル、もしくは関数で取得する必要がある。


	Hyouka Hy;
	Action_manager Ac_m;

	Ac_m.Now_Optim = Hy.hyouka_keisan(FT.points, FT.tiled, FT.agents, FT.my_team_point, FT.other_team_point);






	return 0;
}

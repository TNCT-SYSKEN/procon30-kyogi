#include"SystemManager.h"

void SystemManager::systemManager() {

	Action_manager ACManager;
	Map* map;
	map = map->getMap();


	if (map->turnFlg) {
			
		ACManager.Action();
				
		//評価したのにもう一度評価しないようにする
		map->turnFlg = false;
		map->isCalcOurAction = true;
			   
	}

}



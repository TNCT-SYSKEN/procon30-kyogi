#include"SystemManager.h"

void SystemManager::systemManager() {

	Action_manager ACManager;
	Map* map;
	map = map->getMap();


	if (map->turnFlg) {
			
		ACManager.Action();
				
		//•]‰¿‚µ‚½‚Ì‚É‚à‚¤ˆê“x•]‰¿‚µ‚È‚¢‚æ‚¤‚É‚·‚é
		map->turnFlg = false;
		map->isCalcOurAction = true;
			   
	}

}



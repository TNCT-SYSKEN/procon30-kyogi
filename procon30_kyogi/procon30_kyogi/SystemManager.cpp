#include"SystemManager.h"

void SystemManager::systemManager() {

	Action_manager ACManager;
	Map* map;
	map = map->getMap();


	if (map->turnFlg) {
			
		ACManager.Action();
				
		//�]�������̂ɂ�����x�]�����Ȃ��悤�ɂ���
		map->turnFlg = false;
		map->isCalcOurAction = true;
			   
	}

}



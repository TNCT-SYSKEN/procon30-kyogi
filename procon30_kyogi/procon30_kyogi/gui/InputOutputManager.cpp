#include "InputOutputManager.h"
using namespace std;



void InputOutputManager::init()
{
	CreateMap createMap;
	//jsonなかったら無限ループ
	bool flg=false;
	do {

		flg = createMap.createMapClass();
	} while (!flg);

}


void InputOutputManager::inputOutputManager()
{

}
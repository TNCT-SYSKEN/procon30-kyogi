#include "InputOutputManager.h"
using namespace std;

CreateMap createMap;

void InputOutputManager::init()
{
	//jsonなかったら無限ループ
	bool flg;
	do {

		flg = createMap.createMapClass();
	} while (!flg);

}


void InputOutputManager::inputOutputManager()
{

}
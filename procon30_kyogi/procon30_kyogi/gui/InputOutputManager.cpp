#include "InputOutputManager.h"
using namespace std;

CreateMap createMap;

void InputOutputManager::init()
{
	//json�Ȃ������疳�����[�v
	bool flg;
	do {

		flg = createMap.createMapClass();
	} while (!flg);

}


void InputOutputManager::inputOutputManager()
{

}
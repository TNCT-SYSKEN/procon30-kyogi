#include "InputOutputManager.h"
using namespace std;



void InputOutputManager::init()
{
	CreateMap createMap;
	//json�Ȃ������疳�����[�v
	bool flg=false;
	do {

		flg = createMap.createMapClass();
	} while (!flg);

}


void InputOutputManager::inputOutputManager()
{

}
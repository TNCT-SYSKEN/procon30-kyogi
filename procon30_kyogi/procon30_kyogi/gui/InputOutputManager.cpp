#include "InputOutputManager.h"
using namespace std;

CreateMap createMap;

void InputOutputManager::init()
{
	//json‚È‚©‚Á‚½‚ç–³ŒÀƒ‹[ƒv
	bool flg;
	do {

		flg = createMap.createMapClass();
	} while (!flg);

}


void InputOutputManager::inputOutputManager()
{

}
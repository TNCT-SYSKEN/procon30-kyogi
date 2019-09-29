#include "InputOutputManager.h"
using namespace std;



void InputOutputManager::init()
{
	CreateMap createMap;
	//json‚È‚©‚Á‚½‚ç–³ŒÀƒ‹[ƒv
	bool flg=false;
	do {

		flg = createMap.createMapClass();
	} while (!flg);

}


void InputOutputManager::inputOutputManager()
{

}
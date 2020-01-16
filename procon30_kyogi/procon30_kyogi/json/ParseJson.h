#pragma once
#include <fstream>
#include "../SystemManager.h"
#include "../algorithm/Analysis.h"
#include "picojson.h"
// インクルード漏れがないか確認すること(ここらへん適当)

class ParseJson {
public:
	void writeJsonToText(string,string);
	
	picojson::value readJson(string);
	string getStrPropValue(picojson::value, string);
	int getIntPropValue(picojson::value, string);
	float getFloatPropValue(picojson::value, string);
	
	void parse(string);
	void parseTurn1(string);

	void parseAction(string);
};

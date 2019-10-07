#pragma once
#include <fstream>
#include "../SystemManager.h"
#include "../Data/Map.h"
#include "picojson.h"
// インクルード漏れがないか確認すること(ここらへん適当)

class ParseJson {
public:
	void writeJsonToText(string,string);
	void parse(string);
	picojson::value readJson(string);
	string getStrPropValue(picojson::value, string);
	int getIntPropValue(picojson::value, string);
	float getFloatPropValue(picojson::value, string);
	void parseAction(string);
};

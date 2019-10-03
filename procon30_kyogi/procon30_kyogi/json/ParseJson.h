#pragma once
#include <fstream>
#include <string>
#include "../SystemManager.h"
#include "../Data/Map.h"
#include "picojson.h"
// インクルード漏れがないか確認すること(ここらへん適当)

class ParseJson {
public:
	void parse(string);
	picojson::value readJson(string);
	string getStrPropValue(picojson::value, string);
	int getIntPropValue(picojson::value, string);
};

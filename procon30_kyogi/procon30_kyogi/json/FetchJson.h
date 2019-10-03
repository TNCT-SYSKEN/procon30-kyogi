#pragma once
#include"../SystemManager.h"
#include"data/JsonOption.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include "picojson.h"

class FetchJson {
public:
	void fetchMatches(string, string, string);
	picojson::value readJson(string);
	void fetch();
	
};
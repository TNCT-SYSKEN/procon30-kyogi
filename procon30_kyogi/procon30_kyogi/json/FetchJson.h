#pragma once
#include <fstream>
#include <string>
#include <stdlib.h>
#include "picojson.h"
#include "../SystemManager.h"
#include "data/JsonOption.h"

class FetchJson {
public:
	void fetch(string, string, string, int);
};

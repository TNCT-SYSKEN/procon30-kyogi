#pragma once
#include"../../SystemManager.h"

class JsonOption {
public:

	static JsonOption* getJsonOption();

private:

	static JsonOption* Option;
};
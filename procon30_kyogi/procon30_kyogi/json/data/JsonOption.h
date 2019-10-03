#pragma once
#include"../../SystemManager.h"

class JsonOption {
public:

	string token;
	string port;
	string query;

	static JsonOption* getJsonOption();
private:

	static JsonOption* Option;
};
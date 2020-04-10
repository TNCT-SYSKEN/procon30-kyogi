#pragma once
#include"../../SystemManager.h"

// jsonê›íË Ç∑Ç◊ÇƒÇ±Ç±

class JsonOption {
public:

	// example defalut
	string token = "dbc07e57a1e7b1342c0570d0a4393a53bef552ac2c900f3d2c21dd68a40f3d8b";
	string port = "8080";
	string matchID = "200";

	string query;






	static JsonOption* getJsonOption();
private:

	static JsonOption* Option;
};
#include "FetchJson.h"

void FetchJson::fetch(string token, string port, string query ,int turn) {

	string auth = "\"Authorization: " + token + "\" ";
	string host = "http://127.0.0.1:" + port;
	string path = "/matches/" + query;
	string command = "curl -H " + auth + host + path + " > json/Map/turn"+to_string(turn)+".json";
	system(command.c_str());
}

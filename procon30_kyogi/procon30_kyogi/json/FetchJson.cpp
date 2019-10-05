#include "FetchJson.h"

void FetchJson::fetch(string token, string port, string query) {

	string auth = "\"Authorization: " + token + "\" ";
	string host = "http://127.0.0.1:" + port;
	string path = "/matches/" + query;
	string command = "curl -H " + auth + host + path + " > data.txt";
	system(command.c_str());
}

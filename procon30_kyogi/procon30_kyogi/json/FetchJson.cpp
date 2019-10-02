#include <fstream>
#include <string>
#include <stdlib.h>
#include "picojson.h"

using namespace std;

void fetchMatches(string token, string port, string query) {
	string auth = "\"Authorization: " + token + "\" ";
	string host = "http://127.0.0.1:" + port;
	string path = "/matches/" + query;
	string command = "curl -H " + auth + host + path + " > data.json";
	system(command.c_str());
}

picojson::value readJson(string path) {
	ifstream ifs;
	ifs.open(path);
	picojson::value json;
	ifs >> json;
	ifs.close();
	return json;
}

int main(void) {
	fetchMatches("procon30_example_token", "55669", "");

	cout << readJson("data.json") << endl;

	return 0;
}

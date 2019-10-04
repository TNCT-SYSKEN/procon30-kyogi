#include"CreateJson.h"
using namespace std;

string escapeStr(string str) {
	return "\"" + str + "\"";
}

string CreateJson::createJson()
{
	using v = picojson::value;
	using o = picojson::object;
	using a = picojson::array;



	o l{ {
		"actions", v(a{
			v(o{
				{ "agentID", v(2.0) },
				{ "type", v("move") },
				{ "dx", v(1.0) },
				{ "dy", v(1.0) },
			}),
			v(o{
				{ "agentID", v(3.0) },
				{ "type", v("move") },
				{ "dx", v(-1.0) },
				{ "dy", v(-1.0) },
			})
		})
	} };

	// std::cout << v(l) << std::endl;

	// ファイルにJSONファイル書き込み
	string filename = "WriteJson.txt";
	ofstream ofs(filename);
	ofs << v(l)<< endl;
	// JSON読み取り
	ifstream ifs;
	ifs.open(filename);
	string json;
	ifs >> json;
	ifs.close();

	/*string token = "procon30_example_token";
	string auth = escapeStr("Authorization: " + token) + " ";
	string content_type = escapeStr("Content-Type: application/json") + " ";
	string port = "55021";
	string matchID = "1";
	string host = "http://localhost:" + port + "/matches/" + matchID + "/action ";

*/

	// あとで直す
	/*string command = "curl -H " + auth + "-H " + content_type + "-X POST " + host + "-d " + json;
	cout<<command;
	system(command.c_str());
*/

	return json;
	
}

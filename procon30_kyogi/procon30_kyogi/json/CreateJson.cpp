#include"CreateJson.h"
using namespace std;
/*
string escapeStr(string str) {
	return + str + ";"
}
*/

void CreateJson::createJson()
{
	/*using v = picojson::value;
	using o = picojson::object;
	using a = picojson::array;
	
	o l{ {
		"actions", v(a{
			v(o{
				{ "agentID", v(1.0) },
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
	} };*/
	Agents* agents;
	agents = agents->getAgents();
	///////////////////


	picojson::object lisence;
	picojson::array datalist;

	{
		picojson::object Action;
		Action.insert(make_pair(("dy"), picojson::value(static_cast<double>(agents->ourAgents[0][2]))));
		Action.insert(make_pair(("dx"), picojson::value(static_cast<double>(agents->ourAgents[0][1]))));
		Action.insert(make_pair(("type"), picojson::value("move")));
		Action.insert(make_pair(("agentID"), picojson::value(static_cast<double>(agents->ourAgents[0][0]))));
		
		datalist.push_back(picojson::value(Action));
	}
	lisence.insert(make_pair("actions", picojson::value(datalist)));




	// ファイルにJSONファイル書き込み

	string filename = "json/WriteJson.txt";
	ofstream ofs(filename);
	ofs << picojson::value(lisence) << endl;
	//ofs << v(l)<< map->readTurn<< endl;	
	ofs.close();
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
	string host = "htp://localhost:" + port + "/matches/" + matchID + "/action ";

*/

	// あとで直す
   //string command = "curl -H " + auth + "-H " + content_type + "-X POST " + host + "-d " + json;
	//cout<<command;
	//system(command.c_str());
	//string json = "1";
	
	
}

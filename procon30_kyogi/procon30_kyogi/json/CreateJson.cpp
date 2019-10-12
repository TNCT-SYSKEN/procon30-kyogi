#include"CreateJson.h"

string escapeStr(string str) {
	string ans = "\"" + str + "\"";

	return ans;
}


void CreateJson::createJson(string token,string port,string matchID)
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
	AgentsAction* agentsAcn;
	agentsAcn = agentsAcn->getAgentsAction();
	Field* field;
	field = field->getField();
	Map* map;
	map = map->getMap();
	///////////////////


	picojson::object lisence;
	picojson::array datalist;

	int ourAgentS = agents->ourAgents.size();
	string ActionMove;

	int nowX = 0,nowY=0;

	for (int i = 0; i < ourAgentS; i++) {
		{
		
			picojson::object Action;
			Action.insert(make_pair(("dy"), picojson::value(static_cast<double>(agentsAcn->actionDxDy[i][0].second.second))));
			Action.insert(make_pair(("dx"), picojson::value(static_cast<double>(agentsAcn->actionDxDy[i][0].second.first))));
			
			nowX = agents->ourAgents[i][1] - 1 + agentsAcn->actionDxDy[i][0].second.first;
			nowY = agents->ourAgents[i][2] - 1 + agentsAcn->actionDxDy[i][0].second.second;

			if (agentsAcn->actionDxDy[i][1].second.first == 0 && agentsAcn->actionDxDy[i][2].second.second) {
				ActionMove = "stay";
			}
			else if (field->tiled[nowX][nowY] == map->otherTeamID) {
				ActionMove = "remove";
			}
			else{
				ActionMove = "move";
			}

			Action.insert(make_pair(("type"), picojson::value(ActionMove)));// ActionMove)));
			Action.insert(make_pair(("agentID"), picojson::value(static_cast<double>(agents->ourAgents[i][0]))));

			datalist.push_back(picojson::value(Action));
		}
		
	}
	lisence.insert(make_pair("actions", picojson::value(datalist)));

	// ファイルにJSONファイル書き込み

	string filename = "json/WriteJson.json";
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
	
	
	
	string auth = escapeStr("Authorization: " + token) + " ";
	string content_type = escapeStr("Content-Type: application/json") + " ";
	string host = "http://localhost:" + port + "/matches/" + matchID + "/action ";

	//Action Jsonに
	string SystemJSON = "";
	string filePath = "json/data/Agents/writeJson.json";

	//debug
	for (int i = 0; i < json.size(); i++) {
		if (json[i] == '\"') {
			SystemJSON += '\\';
		}

		SystemJSON += json[i];
		
	}
	//SystemJSON = json;

	ofstream Write(filePath);
	Write << SystemJSON << endl;
	Write.close();

	// あとで直す
	//string command = "curl -H " + auth + "-H " + content_type + "-X POST " + host + "-d ";// 
	string hoge= "curl -H " + auth + "-H " + content_type + "-X POST " + host + "-d " + SystemJSON + "> json/req.json";

	//debug
	system(hoge.c_str());
	
	
}

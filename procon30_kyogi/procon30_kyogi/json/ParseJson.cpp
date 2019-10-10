#include "ParseJson.h"
#include"../gui/DrawData.h"

//ファイルに書き込み
void ParseJson::writeJsonToText(string JSON,string path) {
	// ファイルにJSONファイル書き込み
	string filename = path;
	ofstream ofs(filename);
	ofs << JSON << endl;
}



// ローカルにある JSON ファイルの読み込み
picojson::value ParseJson::readJson(string path) {
	ifstream ifs;
	ifs.open(path);
	picojson::value json;
	ifs >> json;
	ifs.close();
	return json;
}



// string 型でプロパティの値を取得
string ParseJson::getStrPropValue(picojson::value obj, string propName) {
	return (obj.get(propName).to_str());
}

// int 型でプロパティの値を取得
int ParseJson::getIntPropValue(picojson::value obj, string propName) {
	return stoi(getStrPropValue(obj, propName));
}

float ParseJson::getFloatPropValue(picojson::value obj, string propName) {
	return stof(getStrPropValue(obj, propName));
}


// JSON を解析
void ParseJson::parse(string path) {
	
	picojson::value json = readJson(path);
	picojson::object& obj = json.get<picojson::object>();

	Map *map;
	map = map->getMap();
	Field* field;
	field = field->getField();
	Agents* agents;
	agents = agents->getAgents();
	


	//map初期化
	map->score.resize(2, vector<int>(3));
	//map
	map->width = getIntPropValue(json, "width");
	map->vertical = getIntPropValue(json, "height");
	
	map->startedAtUnixTime = getFloatPropValue(json, "startedAtUnixTime");
	map->turn = getIntPropValue(json, "turn");
	
	//field 初期化
	field->points.resize(map->width, vector<int>(map->vertical));
	field->tiled.resize(map->width, vector<int>(map->vertical));
	// tiled
	picojson::array Tiled = obj["tiled"].get <picojson::array>();
	int X = 0, Y = 0;
	for(const auto& tiledY :Tiled) {
		X = 0;
		picojson::array gyou = tiledY.get<picojson::array>();
		for(const auto& tiledX :gyou){
			field->tiled[X][Y] = stoi(tiledX.to_str());
			X++;
		}
		Y++;
	}



	// tiled
	picojson::array Points = obj["points"].get<picojson::array>();
	X = 0, Y = 0;
	for (const auto& PointsY : Points) {
		X = 0;
		picojson::array gyou = PointsY.get<picojson::array>();
		for (const auto& PointsX : gyou) {
			field->points[X][Y] = stoi(PointsX.to_str());
			X++;
		}
		Y++;
	}

	//agents初期化
	agents->ourAgents.resize(8, vector<int>(3));
	agents->otherAgents.resize(8, vector<int>(3));

	// teams
	//i=0がourTeam
	int agentSize = 0;

	picojson::array& teams = obj["teams"].get<picojson::array>();
	for (const auto& li : teams) {
		//agents
		picojson::array agentArray = li.get("agents").get<picojson::array>();
		agentSize = 0;
		for (const auto& aLi : agentArray) {
			
			if(map->ourTeamID==stoi(li.get("teamID").to_str())) {
				//agentID
				agents->ourAgents[agentSize][0] = stoi(aLi.get("agentID").to_str());
				agents->ourAgents[agentSize][1] = stoi(aLi.get("x").to_str());
				agents->ourAgents[agentSize][2] = stoi(aLi.get("y").to_str());
			}
			else {
				agents->otherAgents[agentSize][0] = stoi(aLi.get("agentID").to_str());
				agents->otherAgents[agentSize][1] = stoi(aLi.get("x").to_str());
				agents->otherAgents[agentSize][2] = stoi(aLi.get("y").to_str());

			}
			agentSize++;
		}

		
		if (map->ourTeamID==stoi(li.get("teamID").to_str())) {
			//teamID
			map->ourTeamID = stoi(li.get("teamID").to_str());
			//teamPoint
			map->score[0][1] = stoi(li.get("tilePoint").to_str());
			map->score[0][2] = stoi(li.get("areaPoint").to_str());
			map->score[0][0] = map->score[0][1] + map->score[0][2];


		}
		else {
			//teamID
			map->otherTeamID = stoi(li.get("teamID").to_str());
			//teamPoint
			map->score[1][1] = stoi(li.get("tilePoint").to_str());
			map->score[1][2] = stoi(li.get("areaPoint").to_str());
			map->score[1][0] = map->score[1][1] + map->score[1][2];
		}
	}
	agents->ourAgents.resize(agentSize, vector<int>(3));
	agents->otherAgents.resize(agentSize, vector<int>(3));

	/*vector<vector<int>>stack(agentSize,vector<int>(3));
	stack = agents->ourAgents;
	rep(i, agentSize) {
		agents->ourAgents[i] = stack[agentSize-1 - i];
	}
	stack = agents->otherAgents;
	rep(i, agentSize) {
		agents->otherAgents[i] = stack[agentSize - 1 - i];
	}*/

	
	map->firstJson = true;
	map->turnFlg = true;
	// actions
}






//turn1以降

void ParseJson::parseTurn1(string path) {

	picojson::value json = readJson(path);
	picojson::object& obj = json.get<picojson::object>();

	Map *map;
	map = map->getMap();
	Field* field;
	field = field->getField();
	Agents* agents;
	agents = agents->getAgents();
	AgentsAction* agentsAction;
	agentsAction = agentsAction->getAgentsAction();


	//map初期化
	map->score.resize(2, vector<int>(3));
	//map
	map->width = getIntPropValue(json, "width");
	map->vertical = getIntPropValue(json, "height");

	map->startedAtUnixTime = getFloatPropValue(json, "startedAtUnixTime");
	map->turn = getIntPropValue(json, "turn");

	//field 初期化
	field->points.resize(map->width, vector<int>(map->vertical));
	field->tiled.resize(map->width, vector<int>(map->vertical));
	// tiled
	picojson::array Tiled = obj["tiled"].get <picojson::array>();
	int X = 0, Y = 0;
	for (const auto& tiledY : Tiled) {
		X = 0;
		picojson::array gyou = tiledY.get<picojson::array>();
		for (const auto& tiledX : gyou) {
			field->tiled[X][Y] = stoi(tiledX.to_str());
			X++;
		}
		Y++;
	}



	// tiled
	picojson::array Points = obj["points"].get<picojson::array>();
	X = 0, Y = 0;
	for (const auto& PointsY : Points) {
		X = 0;
		picojson::array gyou = PointsY.get<picojson::array>();
		for (const auto& PointsX : gyou) {
			field->points[X][Y] = stoi(PointsX.to_str());
			X++;
		}
		Y++;
	}

	//agents初期化
	agents->ourAgents.resize(8, vector<int>(3));
	agents->otherAgents.resize(8, vector<int>(3));

	// teams
	//i=0がourTeam
	int i = 0;
	int agentSize = 0;

	picojson::array& teams = obj["teams"].get<picojson::array>();
	for (const auto& li : teams) {
		//agents
		picojson::array agentArray = li.get("agents").get<picojson::array>();
		agentSize = 0;
		for (const auto& aLi : agentArray) {

			if (map->ourTeamID==stoi(aLi.get("agentID").to_str())) {
				//agentID
				agents->ourAgents[agentSize][0] = stoi(aLi.get("agentID").to_str());
				agents->ourAgents[agentSize][1] = stoi(aLi.get("x").to_str());
				agents->ourAgents[agentSize][2] = stoi(aLi.get("y").to_str());
			}
			else {
				agents->otherAgents[agentSize][0] = stoi(aLi.get("agentID").to_str());
				agents->otherAgents[agentSize][1] = stoi(aLi.get("x").to_str());
				agents->otherAgents[agentSize][2] = stoi(aLi.get("y").to_str());
			}
			agentSize++;
		}


		if (map->ourTeamID == stoi(li.get("teamID").to_str())) {
			//teamID
			map->ourTeamID = stoi(li.get("teamID").to_str());
			//teamPoint
			map->score[0][1] = stoi(li.get("tilePoint").to_str());
			map->score[0][2] = stoi(li.get("areaPoint").to_str());
			map->score[0][0] = map->score[0][1] + map->score[0][2];

			i = 1;
		}
		else {
			//teamID
			map->otherTeamID = stoi(li.get("teamID").to_str());
			//teamPoint
			map->score[1][1] = stoi(li.get("tilePoint").to_str());
			map->score[1][2] = stoi(li.get("areaPoint").to_str());
			map->score[1][0] = map->score[1][1] + map->score[1][2];
		}
	}
	agents->ourAgents.resize(agentSize, vector<int>(3));
	agents->otherAgents.resize(agentSize, vector<int>(3));

	/*vector<vector<int>>stack(agentSize,vector<int>(3));
	stack = agents->ourAgents;
	rep(i, agentSize) {
		agents->ourAgents[i] = stack[agentSize-1 - i];
	}
	stack = agents->otherAgents;
	rep(i, agentSize) {
		agents->otherAgents[i] = stack[agentSize - 1 - i];
	}*/
	

	//action代入
//	int agentSize = agents->otherAgents.size();
	

	



	picojson::array& arr = obj["actions"].get<picojson::array>();

	for (const auto& actions : arr) {
		//
		for (int i = 0; i < agentSize; i++) {
			//
			if (agents->ourAgents[i][0] == stoi(actions.get("agentID").to_str())) {
				//ourAgents.x.y+
				agents->ourAgents[i][1] += stoi(actions.get("dx").to_str());
				agents->ourAgents[i][2] += stoi(actions.get("dy").to_str());
			}
			else if (agents->otherAgents[i][0] == stoi(actions.get("agentID").to_str())) {
				//otherAgents.x.y
				agents->otherAgents[i][1] += stoi(actions.get("dx").to_str());
				agents->otherAgents[i][2] += stoi(actions.get("dy").to_str());
			}
			
		}
		/*agentsAction->actionEnemyDxDy[i] = make_pair(
			stoi(actions.get("agentID").to_str()), make_pair(
				stoi(actions.get("dx").to_str()),
				stoi(actions.get("dy").to_str())
			));
		i++;*/
	}




	map->firstJson = true;
	map->turnFlg = true;
	// actions
}



//debug 
void ParseJson::parseAction(string path) {
	AgentsAction* agentsAction;
	agentsAction = agentsAction->getAgentsAction();
	Agents* agents;
	agents = agents->getAgents();

	picojson::value json = readJson(path);
	picojson::object& obj = json.get<picojson::object>();

	Map* map;
	map = map->getMap();

	int agentSize = agents->otherAgents.size();
	agentsAction->actionEnemyDxDy.resize(agentSize);

	picojson::array& arr = obj["actions"].get<picojson::array>();
	int i = 0;
	for (const auto& actions : arr) {
		//
		agentsAction->actionEnemyDxDy[i] = make_pair(
			stoi(actions.get("agentID").to_str()), make_pair(
				stoi(actions.get("dx").to_str()),
				stoi(actions.get("dy").to_str())
			));
		i++;
	}
	
}
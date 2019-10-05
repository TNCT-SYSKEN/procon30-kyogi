#include "ParseJson.h"

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
	picojson::object& obj = json.get<picojson::object()>;
	picojson::value& arr = obj["tiled"].get < picojson::array>.at(0).get<picojson::array>.at(0);

	Map *map;
	map = map->getMap();
	Field* field;
	field = field->getField();
	Agents* agents;
	agents = agents->getAgents();
	


	//map
	map->width = getIntPropValue(json, "width");
	map->vertical = getIntPropValue(json, "height");
	
	map->startedAtUnixTime = getFloatPropValue(json, "startedAtUnixTime");
	map->turn = getIntPropValue(json, "turn");
	
	// points
	rep(i, map->width) {
		rep(j, map->vertical) {
			arr = obj["tiled"].get <picojson::array>.at(j).get<picojson::array>.at(i);
			field->tiled[i][j] = stoi(arr.to_str());
		}
	}
	// tiled
	rep(i, map->width) {
		rep(j, map->vertical) {
			arr = obj["points"].get <picojson::array>.at(j).get<picojson::array>.at(i);
			field->points[i][j] = stoi(arr.to_str());
		}
	}


	// teams
	//i=0がourTeam
	int i = 0;
	int agentSize = 0;

	picojson::array teams = obj["teams"].get<picojson::array>();
	for (const auto& li : teams) {

		//agents
		picojson::array agentArray = li.get("agents").get<picojson::array>();
		for (const auto& aLi : agentArray) {
			agentSize = 0;
			if (i == 0) {
				//agentID
				agents->ourAgents[agentSize][0] = stoi(li.get("agentID").to_str());
				agents->ourAgents[agentSize][1] = stoi(li.get("x").to_str());
				agents->ourAgents[agentSize][2] = stoi(li.get("y").to_str());
			}
			else {
				agents->otherAgents[agentSize][0] = stoi(li.get("agentID").to_str());
				agents->otherAgents[agentSize][1] = stoi(li.get("x").to_str());
				agents->otherAgents[agentSize][2] = stoi(li.get("y").to_str());
			}
			agentSize++;
		}

		
		if (i == 0) {
			//teamID
			map->ourTeamID = stoi(li.get("teamID").to_str());
			//teamPoint
			map->score[0][1] = stoi(li.get("tilePoint").to_str());
			map->score[0][2] = stoi(li.get("arePoint").to_str());
			map->score[0][0] = map->score[0][1] + map->score[0][2];

			i = 1;
		}
		else {
			//teamID
			map->otherTeamID = stoi(li.get("teamID").to_str());
			//teamPoint
			map->score[1][1] = stoi(li.get("tilePoint").to_str());
			map->score[1][2] = stoi(li.get("arePoint").to_str());
			map->score[1][0] = map->score[1][1] + map->score[1][2];
		}

	}


	// actions
}

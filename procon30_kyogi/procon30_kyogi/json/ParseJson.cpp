#include "ParseJson.h"

//debug mode
void ParseJson::writeJsonToText(string JSON) {
	// �t�@�C����JSON�t�@�C����������
	string filename = "data.txt";
	ofstream ofs(filename);
	ofs << JSON << endl;
}


// ���[�J���ɂ��� JSON �t�@�C���̓ǂݍ���
picojson::value ParseJson::readJson(string path) {
	ifstream ifs;
	ifs.open(path);
	picojson::value json;
	ifs >> json;
	ifs.close();
	return json;
}

// string �^�Ńv���p�e�B�̒l���擾
string ParseJson::getStrPropValue(picojson::value obj, string propName) {
	return (obj.get(propName).to_str());
}

// int �^�Ńv���p�e�B�̒l���擾
int ParseJson::getIntPropValue(picojson::value obj, string propName) {
	return stoi(getStrPropValue(obj, propName));
}

float ParseJson::getFloatPropValue(picojson::value obj, string propName) {
	return stof(getStrPropValue(obj, propName));
}


// JSON �����
void ParseJson::parse(string path) {
	picojson::value json = readJson(path);
	picojson::object& obj = json.get<picojson::object>();

	Map *map;
	map = map->getMap();
	Field* field;
	field = field->getField();
	Agents* agents;
	agents = agents->getAgents();
	


	//map������
	map->score.resize(2, vector<int>(3));
	//map
	map->width = getIntPropValue(json, "width");
	map->vertical = getIntPropValue(json, "height");
	
	map->startedAtUnixTime = getFloatPropValue(json, "startedAtUnixTime");
	map->turn = getIntPropValue(json, "turn");
	
	//field ������
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

	//agents������
	agents->ourAgents.resize(8, vector<int>(3));
	agents->otherAgents.resize(8, vector<int>(3));

	// teams
	//i=0��ourTeam
	int i = 0;
	int agentSize = 0;

	picojson::array& teams = obj["teams"].get<picojson::array>();
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
	agents->ourAgents.resize(agentSize, vector<int>(3));
	agents->otherAgents.resize(agentSize, vector<int>(3));


	// actions
}

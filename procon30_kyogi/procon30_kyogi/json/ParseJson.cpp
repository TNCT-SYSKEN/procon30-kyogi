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
	return obj.get(propName).to_str();
}

// int 型でプロパティの値を取得
int ParseJson::getIntPropValue(picojson::value obj, string propName) {
	return stoi(getStrPropValue(obj, propName))
}

// JSON を解析
void ParseJson::parse(string path) {
	picojson::value json = readJson(path);
	Map *map;
	map = map->getMap();

	map->width = getIntPropValue(json, "width");
	map->height = getIntPropValue(json, "height");
	// points
	map->startedAtUnixTime = getIntPropValue(json, "startedAtUnixTime");
	map->turn = getIntPropValue(json, "turn");
	// tiled
	// teams
	// actions
}

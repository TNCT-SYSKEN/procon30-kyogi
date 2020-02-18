#pragma once
#include"../general.h"

class Field {
public:
	//TilePoints
	vector<vector<int>> points;
	//TiledPoints
	vector<vector<int>> tiled;


	vector<vector<vector<int>>> turnTiled;
	//ターンの中に その時その時のエージェント
	vector<vector<pair<int, int>>>turnAgent;

	static Field* getField();



	vector<vector<int>> AnalysisField;
	vector<vector<int>> evalutionField;


private:
	static Field* field;
};
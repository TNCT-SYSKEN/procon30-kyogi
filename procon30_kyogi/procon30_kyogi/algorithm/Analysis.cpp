#include"Analysis.h"

void Analysis::AnalysisCalc() {
	Field* field;
	field = field->getField();
	Map* map;
	map = map->getMap();

	vector<vector<int>> AnalysField;
	AnalysField.resize(map->width, vector<int>(map->vertical,0));
	
	int dx[] = { 1,1,1,0,0,-1,-1,-1 };
	int dy[] = { 1,0,-1,1,-1,1,0,-1 };

	int nowX = 0;
	int nowY = 0;

	rep(j, map->vertical) {
		nowX = 0;
		
		rep(i, map->width) {
			
			rep(count, 8) {
				if (nowX + dx[count] < 0 || nowX + dx[count] >= map->width || nowY + dy[count] < 0 || nowY + dy[count] >= map->vertical)continue;
				
				else {
					if (field->points[nowX][nowY] < 0) {

						AnalysField[nowX + dx[count]][nowY + dy[count]] += abs(field->points[nowX][nowY]);

					}
					else {

						AnalysField[nowX + dx[count]][nowY + dy[count]] += field->points[nowX][nowY];

					}

				}
			}
			nowX++;
		}
		nowY++;
	}
	
	field->AnalysisField.resize(map->width, vector <int>(map->vertical));
	
	field->AnalysisField = AnalysField;


	map->AnalysCalcC = true;
}
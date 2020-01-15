#include"../Data/Map.h"
#include"../Data/Agents.h"

class ManualInput
{
public:
	void mousePosition();
	void onMap(const int posx, const int posy);
	void onMapAgents(const int posx, const int posy);
	void clickedMap(const int x, const int y);
};


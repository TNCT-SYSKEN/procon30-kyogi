#include <iostream>
#include <time.h>
#include "picojson.h"

int main()
{
	using v = picojson::value;
	using o = picojson::object;
	using a = picojson::array;

	o l{ {
		" actions", v(a{
			v(o{
				{ "agentID", v(9.0) },
				{ "type", v("move") },
				{ "dx", v(1.0) },
				{ "dy", v(1.0) },
			}),
			v(o{
				{ "agentID", v(10.0) },
				{ "type", v("move") },
				{ "dx", v(-1.0) },
				{ "dy", v(-1.0) },
			})
		})
	} };

	std::cout << v(l) << std::endl;
}







/*#include <iostream>
#include <time.h>
#include "picojson.h"

int main()
{
	picojson::object actions; 
	picojson::array datalist;
	using v = picojson::value;
	{
		actions.insert({ "agentID", v("9") });
		actions.insert({ "type", v("move") });
		actions.insert({ "dx", v("1") });
		actions.insert({ "dy", v("1") });

		//datalist.push_back(picojson::value(dy));
	}

	/*{

		picojson::object agentID;
		agentID.insert({ "agentID", v("10") });

		picojson::object type;
		type.insert({ "type", v("move") });

		picojson::object dx;
		dx.insert({ "dx", v("-1") });

		picojson::object dy;
		dy.insert({ "dy", v("-1") });

		dy.insert({ "agentID", v(agentID) });

		//datalist.push_back(picojson::value(dy));
	}

	actions.insert({ "actions", v(datalist) });

	std::cout << v(actions) << std::endl;
}*/
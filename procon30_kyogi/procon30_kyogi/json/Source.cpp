#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include "picojson.h"
//C:\Users\友末　智将\Desktop\test - json
//C:\Users\友末　智将\Downloads\picojson - master\picojson - master
int main(void)
{
	// JSONデータの読み込み。
	std::ifstream ifs("フィールド情報_turn0.json", std::ios::in);
	if (ifs.fail()) {
		std::cerr << "failed to read フィールド情報_turn0.json" << std::endl;
		return 1;
	}
	const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	ifs.close();

	// JSONデータを解析する。
	picojson::value v;
	const std::string err = picojson::parse(v, json);
	if (err.empty() == false) {
		std::cerr << err << std::endl;
		return 2;
	}

	picojson::object& obj = v.get<picojson::object>();
	std::cout << "width: " << obj["width"].get<double>() << std::endl;
	std::cout << "height: " << obj["height"].get<double>() << std::endl;
	std::cout << "startedAtUnixTime: " << obj["startedAtUnixTime"].get<double>() << std::endl;
	std::cout << "turn: " << obj["turn"].get<double>() << std::endl;
	std::cout << "points: ";
	picojson::array& ary = obj["points"].get<picojson::array>();
	for (const auto& e : ary) {  // vectorをrange-based-forでまわしている。
		std::cout << e.get<std::string>() << " ";
	}

	return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include "picojson.h"
//C:\Users\�F���@�q��\Desktop\test - json
//C:\Users\�F���@�q��\Downloads\picojson - master\picojson - master
int main(void)
{
	// JSON�f�[�^�̓ǂݍ��݁B
	std::ifstream ifs("�t�B�[���h���_turn0.json", std::ios::in);
	if (ifs.fail()) {
		std::cerr << "failed to read �t�B�[���h���_turn0.json" << std::endl;
		return 1;
	}
	const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	ifs.close();

	// JSON�f�[�^����͂���B
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
	for (const auto& e : ary) {  // vector��range-based-for�ł܂킵�Ă���B
		std::cout << e.get<std::string>() << " ";
	}

	return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <cassert>
#include "picojson.h"
//C:\Users\�F���@�q��\Desktop\test - json
//C:\Users\�F���@�q��\Downloads\picojson - master\picojson - master
using namespace std;
using namespace picojson;

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

	//picojson::array& ary = obj["points"].get<picojson::array>(); 
	//cout << "points:" << endl;
	/*for (const auto& e : ary) {  // vector��range-based-for�ł܂킵�Ă���B
		std::cout << e.get<std::string>() << " ";
	}*/
	
	/*int main() {
		// Declaration
		stringstream ss;
		ifstream     f;
		unsigned int i;

		// Read Json file
		f.open("�t�B�[���h���_turn0.json", ios::binary);
		if (!f.is_open()) return 1;
		ss << f.rdbuf();
		f.close();

		// Parse Json data
		value v;
		ss >> v;
		string err = get_last_error();
		if (!err.empty()) {
			cerr << err << endl;
			return -1;
		}
		object& o = v.get<object>();
		picojson::array& aAry = o["points"].get<picojson::array>();
		cout << "points:" << endl;
		for (i = 0; i < aAry.size(); i++)
			cout << "\t" << aAry[i].get<string>() << endl;

	/*for (picojson::array::iterator it = ary.begin(); it != ary.end(); it++)
	{
		cout << get<string> << " ";
	}*/

	picojson::object& obj = v.get<picojson::object>();
	std::cout << "width: " << obj["width"].get<double>() << std::endl;
	std::cout << "height: " << obj["height"].get<double>() << std::endl;
	std::cout << "startedAtUnixTime: " << obj["startedAtUnixTime"].get<double>() << std::endl;
	std::cout << "turn: " << obj["turn"].get<double>() << std::endl;
	std::cout << "points" << obj["points"].get<picojson::array>().at(0);

	return 0;
}
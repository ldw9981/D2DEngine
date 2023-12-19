#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

const auto JSON_INDENT = 2;
const std::string strJson = R"(
    {
      "id" : 123456,
      "res" : 111.222,
      "name" : "Example Json",
      "desc" : "Hello, SnowDeer",
      "data" : [
        {
          "id" : 101,
          "name" : "snowdeer"
        },
        {
          "id" : 202,
          "name" : "ice-rabbit"
        }
      ],
      "info" : {
        "notebook" : "macbook m1 pro",
        "address" : "Seoul"
      }
    }
  )";

void createJsonObjectTest() {
	std::cout << "### Create JSON Object ###" << std::endl;

	json obj;
	obj["id"] = 0;
	obj["data"]["name"] = "snowdeer";
	obj["data"]["age"] = 45;
	obj["data"]["address"] = "Seoul";

	std::cout << obj.dump(JSON_INDENT) << std::endl;
}

void createJsonArrayTest() {
	std::cout << "### Create JSON Array ###" << std::endl;

	json objs;
	objs.push_back("snowdeer");
	objs.push_back("ice-rabbit");
	objs.push_back("fire-bat");

	std::cout << objs.dump(JSON_INDENT) << std::endl;
}

void createMixedJsonObjectTest() {
	std::cout << "### Create Mixed JSON Object ###" << std::endl;

	json obj1 = { {"id", 1},
				 {"name", "snowdeer"},
				 {"age", 45} };

	json obj2 = { {"id", 2},
				 {"name", "ice-rabbit"},
				 {"age", 32} };

	json obj3 = { {"id", 3},
				 {"name", "fire-bat"},
				 {"age", 28} };

	json objs;
	objs.push_back(obj1);
	objs.push_back(obj2);
	objs.push_back(obj3);

	std::cout << objs.dump(JSON_INDENT) << std::endl;
}

void parseJsonTest() {
	std::cout << "### parseJson Test ###" << std::endl;

	auto j = json::parse(strJson);
	std::cout << j.dump(JSON_INDENT) << std::endl;
	std::cout << j["data"].dump(JSON_INDENT) << std::endl;
	std::cout << j["datxxx"].dump(JSON_INDENT) << std::endl;      // 잘못된 Key에 대해서는 null
	//  std::cout << j["data"]["name"].dump(JSON_INDENT) << std::endl;    // 배열을 이런 식으로 접근하면 Exception
	std::cout << j["data"][0]["name"].dump(JSON_INDENT) << std::endl;
}

std::string getTypeOfValue(json value) {
	if (value.is_array()) return "array";
	if (value.is_boolean()) return "boolean";
	if (value.is_null()) return "null";
	if (value.is_number_integer()) return "integer";
	if (value.is_number_float()) return "double";
	if (value.is_string()) return "string";
	if (value.is_object()) return "object";

	return "Unknown";
}

void getKeyValueListTest() {
	std::cout << "### Key Value Test ###" << std::endl << std::endl;;

	auto j = json::parse(strJson);
	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		std::cout << "Key : \"" << it.key() << "\"" << std::endl;
		std::cout << "Type : " << getTypeOfValue(it.value()) << std::endl;
		std::cout << "Value : " << it.value() << std::endl;
		std::cout << std::endl;
	}
}

void recursive(json j, int space) {
	std::string indent = "";
	for (auto i = 0; i < space; i++) {
		indent = indent + " ";
	}
	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		std::cout << indent << "Key : \"" << it.key() << "\"" << std::endl;

		if (it.value().is_array()) {
			std::cout << indent << "[" << std::endl;
			for (auto item : it.value()) {
				recursive(item, space + 2);
			}
			std::cout << indent << "]" << std::endl;
		}
		if (it.value().is_object()) {
			std::cout << indent << "{" << std::endl;
			recursive(j[it.key()], space + 2);
			std::cout << indent << "}" << std::endl;
		}

	}
}

void recursiveParseJsonTest() {
	std::cout << "### Recursive parse Json Test ###" << std::endl;

	auto j = json::parse(strJson);
	recursive(j, 0);

}
/*
int _main() {
	std::cout << "Hello, World!" << std::endl;

	//  createJsonObjectTest();
	//  createJsonArrayTest();
	//  createMixedJsonObjectTest();

	//  parseJsonTest();
	//  getKeyValueListTest();
	recursiveParseJsonTest();

	return 0;
}
*/
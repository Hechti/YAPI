#include "YapiProperty.h"
#include <iostream>
#include <fstream>

yapi::Property::Property(std::string filename)
{
    std::ifstream file;

    file.open(filename, std::ios_base::in);
    if (!file) {
        std::string error = std::string("File not found: ") + filename;
        throw std::exception(error.c_str()) ;
    }
    nlohmann::json j;
    file >> j;
    properties = j["plugins"];
    nlohmann::json filter = properties[0];
    std::string test = filter["name"];
    std::cout << test;
}


nlohmann::json yapi::Property::GetPluginProperties(std::string name, int instance)
{
    for (nlohmann::json::iterator it = properties.begin(); it != properties.end(); ++it) {
        std::cout << *it<< std::endl;
        std::cout << (*it)["name"] << std::endl;
        if ((*it)["name"] == name && (*it)["instance"] == instance) {
            return *it;
        }
    }
    return nlohmann::json();
}

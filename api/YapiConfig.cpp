#include "YapiConfig.h"
#include <iostream>
#include <fstream>

yapi::Config yapi::Config::FromFile(std::string pluginName, int pluginInstance, std::string filename)
{
    std::ifstream file;
    file.open(filename, std::ios_base::in);
    if (!file) {
        std::string error = std::string("File not found: ") + filename;
        throw std::exception(error.c_str());
    }
    nlohmann::json j;
    file >> j;
    nlohmann::json properties = j["plugins"];
    if (properties.is_null()) {
        throw std::exception("File contains no plugins section");
    }

    for (nlohmann::json::iterator it = properties.begin(); it != properties.end(); ++it) {
        std::cout << *it << std::endl;
        std::cout << (*it)["name"] << std::endl;
        if ((*it)["name"] == pluginName && (*it)["instance"] == pluginInstance) {
            return Config(*it);
        }
    }

    return Config();
}

#include "json.hpp"
#include <iostream>

namespace yapi {
    class Property {
    public:
        explicit Property(std::string filename);
        ~Property() = default;

        nlohmann::json getPluginProperties(std::string name, int instance);

    private:
        nlohmann::json properties;
    };


    class Config {
    public:
        explicit Config(nlohmann::json config) :m_config (config) {};

        ~Config() = default;


        template<typename Default, typename ...Rest>
        Default getParameter(Default default, Rest... rest) {
            m_requested_config = merge(m_requested_config, _set_requested_config(default, rest...));
            return _getParameter(default, m_config, rest...);
        }

        template<typename ...Rest>
        std::string getParameter(const char* default, Rest... rest) {
            m_requested_config = merge(m_requested_config, _set_requested_config(default, rest...));
            return _getParameter(std::string(default), m_config, rest...);
        }
    private:
        template<typename Default, typename Key, typename ...Rest>
        Default _getParameter(Default default, nlohmann::json content, Key key, Rest... rest) {
                return _getParameter(default, content[key], rest...);

        };

        template<typename Default, typename Key>
        Default _getParameter(Default default, nlohmann::json content, Key key) {
            nlohmann::json value = content[key];
            if (value.is_null()) {
                return default;
            }
            else {
                return value;
            }
        }

        template<typename Default, typename Key, typename ...Rest>
        nlohmann::json _set_requested_config(Default default, Key key, Rest... rest)
        {
            nlohmann::json value;
            value[key] = _set_requested_config(default, rest...);
            return value;
        }

        template<typename Default>
        nlohmann::json _set_requested_config(Default default)
        {
                return default;
        }

        // merge function from https://github.com/nlohmann/json/issues/252#issuecomment-222312519
        nlohmann::json merge(const nlohmann::json &a, const nlohmann::json &b)
        {
            nlohmann::json result = a.flatten();
            nlohmann::json tmp = b.flatten();

            for (nlohmann::json::iterator it = tmp.begin(); it != tmp.end(); ++it)
            {
                result[it.key()] = it.value();
            }

            return result.unflatten();
        }
    
    public:
        nlohmann::json m_config;
        nlohmann::json m_requested_config;


    };

}
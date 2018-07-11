#include "json/json.hpp"
#include <iostream>

namespace yapi
{

    class Config
	{
    public:
        static yapi::Config FromFile(std::string pluginName, int pluginInstance, std::string filename);

    public:
        Config() { m_config = nlohmann::json(); }
        explicit Config(nlohmann::json config) :m_config (config) {};

        ~Config() = default;

        template<typename Default, typename ...Rest>
        Default GetParameter(Default default, Rest... rest)
		{
            m_requested_config = MergeJson(m_requested_config, _SetRequestedConfig(default, rest...));
            return _GetParameter(default, m_config, rest...);
        }

        template<typename ...Rest>
        std::string GetParameter(const char* default, Rest... rest)
		{
            m_requested_config = MergeJson(m_requested_config, _SetRequestedConfig(default, rest...));
            return _GetParameter(std::string(default), m_config, rest...);
        }

        nlohmann::json GetRequestedConfig() const;

    private:
        template<typename Default, typename Key, typename ...Rest>
        Default _GetParameter(Default default, nlohmann::json content, Key key, Rest... rest)
		{
                return _GetParameter(default, content[key], rest...);
        };

        template<typename Default, typename Key>
        Default _GetParameter(Default default, nlohmann::json content, Key key)
		{
            nlohmann::json value = content[key];
            if (value.is_null()) {
                return default;
            }
            else {
                return value;
            }
        }

        template<typename Default, typename Key, typename ...Rest>
        nlohmann::json _SetRequestedConfig(Default default, Key key, Rest... rest)
        {
            nlohmann::json value;
            value[key] = _SetRequestedConfig(default, rest...);
            return value;
        }

        template<typename Default>
        nlohmann::json _SetRequestedConfig(Default default)
        {
            return default;
        }

		nlohmann::json MergeJson(const nlohmann::json &a, const nlohmann::json &b);
 
  
    private:
        nlohmann::json m_config;
        nlohmann::json m_requested_config;
    };

}
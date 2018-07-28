#include "json/json.hpp"
#include <iostream>

namespace yapi
{

    class Config
	{
    public:
        static yapi::Config FromFile(const std::string& pluginName, int pluginInstance, const std::string& filename);

    public:
        Config() : m_config(nlohmann::json()) {}
        explicit Config(nlohmann::json config) :m_config (config) {};

        ~Config() = default;

        template<typename Default, typename ...Rest>
        Default GetParameter(Default defaultParameter, Rest... rest)
		{
            m_requested_config = MergeJson(m_requested_config, _SetRequestedConfig(defaultParameter, rest...));
            return _GetParameter(defaultParameter, m_config, rest...);
        }

        template<typename ...Rest>
        std::string GetParameter(const char* defaultParameter, Rest... rest)
		{
            m_requested_config = MergeJson(m_requested_config, _SetRequestedConfig(defaultParameter, rest...));
            return _GetParameter(std::string(defaultParameter), m_config, rest...);
        }

        nlohmann::json GetRequestedConfig() const;

    private:
        template<typename Default, typename Key, typename ...Rest>
        Default _GetParameter(Default defaultParameter, nlohmann::json content, Key key, Rest... rest)
		{
                return _GetParameter(defaultParameter, content[key], rest...);
        };

        template<typename Default, typename Key>
        Default _GetParameter(Default defaultParameter, nlohmann::json content, Key key)
		{
            nlohmann::json value = content[key];
            if (value.is_null()) {
                return defaultParameter;
            }
            else {
                return value;
            }
        }

        template<typename Default, typename Key, typename ...Rest>
        nlohmann::json _SetRequestedConfig(Default defaultParameter, Key key, Rest... rest)
        {
            nlohmann::json value;
            value[key] = _SetRequestedConfig(defaultParameter, rest...);
            return value;
        }

        template<typename Default>
        nlohmann::json _SetRequestedConfig(Default defaultParameter)
        {
            return defaultParameter;
        }

		nlohmann::json MergeJson(const nlohmann::json &a, const nlohmann::json &b);
 
  
    private:
        nlohmann::json m_config;
        nlohmann::json m_requested_config;
    };

}
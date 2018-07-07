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

            _set_requested_config(default, std::forward<Rest>(rest)...);
            return _getParameter(default, m_config, rest...);
        }

        template<typename ...Rest>
        std::string getParameter(const char* default, Rest... rest) {
            _set_requested_config(default, std::forward<Rest>(rest)...);
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

        template<typename Default, typename Key>
        void _set_requested_config(Default default, Key key, ...) {
            va_list args;
            va_start(args, key);

            while (*fmt != '\0') {
                if (*fmt == 'd') {
                    int i = va_arg(args, int);
                    std::cout << i << '\n';
                }
                else if (*fmt == 'c') {
                    // note automatic conversion to integral type
                    int c = va_arg(args, int);
                    std::cout << static_cast<char>(c) << '\n';
                }
                else if (*fmt == 'f') {
                    double d = va_arg(args, double);
                    std::cout << d << '\n';
                }
                ++fmt;
            }

            va_end(args);
        }

    
    private:
        nlohmann::json m_config;
        nlohmann::json m_requested_config;


    };

}
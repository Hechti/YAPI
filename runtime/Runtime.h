#ifndef YAPI_RUNTIME
#define YAPI_RUNTIME

#include <Yapi.h>
#include <vector>
#include <map>
#include <memory>

namespace yapi
{
  class Runtime
  {
  public:
    using PluginPathList = std::vector<std::string>;

  public:
    Runtime(const PluginPathList& pluginPathList);
    ~Runtime();

  public:
    void LoadConfig(const std::string& configPath);
    void Start();
    void Stop();

  private:
    using LoadedPluginList = std::map<std::string, std::shared_ptr<YAPI>>;
    LoadedPluginList m_loadedPluginList;
  };
}


#endif
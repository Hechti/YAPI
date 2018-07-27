#include "Runtime.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <json/json.hpp>


namespace yapi
{
	constexpr char const* create_plugin = "createPlugin";

	namespace config
	{
		constexpr char const* connections = "connections";
		constexpr char const* name_src = "name_src";
		constexpr char const* name_dst = "name_dst";
		constexpr char const* pin_src = "pin_src";
		constexpr char const* pin_dst = "pin_dst";
	}
}

typedef yapi::YAPI* (*CreatePluginFunc)(void);

yapi::Runtime::Runtime(const PluginPathList& pluginPathList)
{
  for (auto& pluginName : pluginPathList) {
    HINSTANCE handle = LoadLibrary(pluginName.c_str());
    if (handle == nullptr) {
      std::cout << "Failed to load plugin " << pluginName << std::endl;
      continue;
    }

    CreatePluginFunc createPlugin = (CreatePluginFunc)GetProcAddress(handle, yapi::create_plugin);
    if (createPlugin == nullptr) {
      std::cout << "Failed to get address of \"createPlugin\" function of plugin " << pluginName << std::endl;
      continue;
    }

    std::shared_ptr<yapi::YAPI> plugin = std::shared_ptr<yapi::YAPI>(createPlugin());
    m_loadedPluginList[plugin->GetPluginName()] = plugin;
    std::cout << "Loaded " << plugin->GetPluginName() << std::endl;
  }
}

yapi::Runtime::~Runtime()
{

}

void yapi::Runtime::LoadConfig(const std::string& configPath)
{
  std::ifstream file(configPath);
  nlohmann::json jsonFile;
  file >> jsonFile;

  auto connections = jsonFile.find(yapi::config::connections);
  if (connections == jsonFile.end()) {
    throw std::exception("no connections found");
  }

  for (auto& element : connections.value()) {
    auto& pluginSrcName = element.find(config::name_src).value();
    const auto& pluginSrc = m_loadedPluginList.find(pluginSrcName);
    if (pluginSrc == m_loadedPluginList.end()) {
      std::cout << "Unable to find plugin \"" << pluginSrcName << "\"" << std::endl;
      continue;
    }

    auto& pluginDstName = element.find(config::name_dst).value();
    const auto& pluginDst = m_loadedPluginList.find(pluginDstName);
    if (pluginDst == m_loadedPluginList.end()) {
      std::cout << "Unable to find plugin \"" << pluginDstName << "\"" << std::endl;
      continue;
    }

    // pluginSrc->second->Connect(element.find(config::pin_src).value(), pluginDst->second->GetInputPin(element.find(config::pin_dst).value()));
    yapi::Connect(pluginSrc->second.get(), element.find(config::pin_src).value(), pluginDst->second.get(), element.find(config::pin_dst).value());
  }
}

void yapi::Runtime::Start()
{
  const std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

  for (auto& plugin : m_loadedPluginList) {
    plugin.second->SetStartTime(startTime);
  }

  for (auto& plugin : m_loadedPluginList) {
    plugin.second->Start();
  }
}

void yapi::Runtime::Stop()
{
  for (auto& plugin : m_loadedPluginList) {
    plugin.second->Stop();
  }
}

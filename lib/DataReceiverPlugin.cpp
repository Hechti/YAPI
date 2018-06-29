#include "DataReceiverPlugin.h"
#include <iostream>

DataReceiverPlugin::DataReceiverPlugin() : m_pin("Input")
{
  RegisterPin(m_pin);
}

DataReceiverPlugin::~DataReceiverPlugin()
{

}

void DataReceiverPlugin::SampleReceivedEvent(const std::string& pinName, const char*const buffer, const size_t bufferSize)
{
  const int*const value = reinterpret_cast<const int*const>(buffer);
  std::cout << "Received value: " << *value << std::endl;
}

void DataReceiverPlugin::Start()
{

}

void DataReceiverPlugin::Stop()
{

}

std::string DataReceiverPlugin::GetPluginName() const
{
  return "DataReceiverPlugin";
}

CREATE_PLUGIN(DataReceiverPlugin)
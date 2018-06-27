#include "DataSenderPlugin.h"

DataSenderPlugin::DataSenderPlugin() : m_pin("Output")
{
  RegisterPin(m_pin);
}

DataSenderPlugin::~DataSenderPlugin()
{

}

void DataSenderPlugin::SampleReceivedEvent(const std::string& pinName, const char*const buffer, const size_t bufferSize)
{

}

void DataSenderPlugin::Start()
{
  const int value = 2211;
  m_pin.Transmit(reinterpret_cast<const char*const>(&value), sizeof(int));
}

std::string DataSenderPlugin::GetPluginName() const
{
  return "DataSenderPlugin";
}

extern "C" {
  __declspec(dllexport) DataSenderPlugin* createPlugin()
  {
    return new DataSenderPlugin();
  }
}
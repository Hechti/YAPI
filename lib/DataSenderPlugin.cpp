#include "DataSenderPlugin.h"

DataSenderPlugin::DataSenderPlugin() : m_pin("Output"), m_sendThread(nullptr), m_stopThread(false)
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
  int value = 0;

  m_sendThread.reset(new std::thread(&DataSenderPlugin::SendValue, this));
}

void DataSenderPlugin::Stop()
{
  m_stopThread = true;
  m_sendThread->join();
}

std::string DataSenderPlugin::GetPluginName() const
{
  return "DataSenderPlugin";
}

void DataSenderPlugin::SendValue()
{
  // start first execution delayed
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  int value = 0;
  while (!m_stopThread) {
    m_pin.Transmit(reinterpret_cast<const char*const>(&value), sizeof(int));
    value++;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

CREATE_PLUGIN(DataSenderPlugin)
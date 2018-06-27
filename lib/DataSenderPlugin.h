#ifndef DATA_SENDER_PLUGIN
#define DATA_SENDER_PLUGIN

#include <PluginAPI.h>
using namespace yapi;

class DataSenderPlugin : public YAPI
{
public:
  DataSenderPlugin();
  virtual ~DataSenderPlugin();

public:
  virtual void SampleReceivedEvent(const std::string& pinName, const char*const buffer, const size_t bufferSize) override;
  virtual void Start() override;
  virtual std::string GetPluginName() const override;

private:
  OutputPin m_pin;
};

#endif
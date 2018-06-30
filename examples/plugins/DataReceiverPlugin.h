#ifndef DATA_RECEIVER_PLUGIN
#define DATA_RECEIVER_PLUGIN

#include <Yapi.h>
using namespace yapi;

class DataReceiverPlugin : public YAPI
{
public:
  DataReceiverPlugin();
  virtual ~DataReceiverPlugin();

public:
  virtual void SampleReceivedEvent(const std::string& pinName, const char*const buffer, const size_t bufferSize) override;
  virtual void Start() override;
  virtual void Stop() override;
  virtual std::string GetPluginName() const override;

private:
  InputPin m_pin;
};

#endif
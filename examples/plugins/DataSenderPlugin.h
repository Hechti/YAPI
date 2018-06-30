#ifndef DATA_SENDER_PLUGIN
#define DATA_SENDER_PLUGIN

#include <Yapi.h>
using namespace yapi;

#include <thread>
#include <atomic>

class DataSenderPlugin : public YAPI
{
public:
  DataSenderPlugin();
  virtual ~DataSenderPlugin();

public:
  virtual void SampleReceivedEvent(const std::string& pinName, const char*const buffer, const size_t bufferSize) override;
  virtual void Start() override;
  virtual void Stop() override;
  virtual std::string GetPluginName() const override;

  void SendValue();

private:
  OutputPin m_pin;
  std::unique_ptr<std::thread> m_sendThread;
  std::atomic_bool m_stopThread;
};

#endif
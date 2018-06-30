#ifndef YAPI_SAMPLE_EVENT_HANDLER
#define YAPI_SAMPLE_EVENT_HANDLER

namespace yapi
{
  class SampleEventHandler
  {
  public:
    virtual ~SampleEventHandler() {}
    virtual void SampleReceivedEvent(const std::string& pinName, const char*const buffer, const size_t bufferSize) = 0;
  };
}

#endif
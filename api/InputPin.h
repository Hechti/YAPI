#ifndef YAPI_INPUT_PIN
#define YAPI_INPUT_PIN

#include <string>

namespace yapi
{
  class SampleEventHandler;

  class InputPin
  {
  public:
    InputPin(const std::string& name);

  public:
    void SetSampleEventHandler(SampleEventHandler* event);
    SampleEventHandler* GetSampleEventHandler();
    const std::string& GetName() const;

  private:
    SampleEventHandler * m_onPinEvent;
    std::string m_name;
  };
}

#endif

#ifndef YAPI_OUTPUT_PIN
#define YAPI_OUTPUT_PIN

#include <string>
#include <vector>

namespace yapi
{
  class InputPin;

  class OutputPin
  {
  public:
    OutputPin(const std::string& name);
    void Connect(InputPin* pin);
    void Transmit(const char*const buffer, const size_t bufferSize);
    const std::string& GetName() const;

  private:
    std::string m_name;
    using InputPinList = std::vector<InputPin*>;
    InputPinList m_inputPinList;
  };
}

#endif

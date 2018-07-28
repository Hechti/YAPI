#include "OutputPin.h"
#include "InputPin.h"
#include "SampleEventHandler.h"

yapi::OutputPin::OutputPin(const std::string& name) : m_name(name)
{
 
}

void yapi::OutputPin::Connect(InputPin& pin)
{
  m_inputPinList.push_back(pin);
}

void yapi::OutputPin::Transmit(const char*const buffer, const size_t bufferSize)
{
  for (InputPin& pin : m_inputPinList) {
    pin.GetSampleEventHandler()->SampleReceivedEvent(pin.GetName(), buffer, bufferSize);
  }
}

const std::string& yapi::OutputPin::GetName() const
{
  return m_name;
}


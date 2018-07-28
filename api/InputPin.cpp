#include "InputPin.h"
#include "SampleEventHandler.h"

yapi::InputPin::InputPin(const std::string& name) : m_name(name), m_onPinEvent(nullptr)
{
 
}

void yapi::InputPin::SetSampleEventHandler(SampleEventHandler* event)
{
  m_onPinEvent = event;
}

yapi::SampleEventHandler* yapi::InputPin::GetSampleEventHandler()
{
  if (m_onPinEvent == nullptr) {
    throw std::exception("SampleEventHandler is not set!");
  }

  return m_onPinEvent;
}

const std::string& yapi::InputPin::GetName() const
{
  return m_name;
}

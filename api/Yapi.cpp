#include "Yapi.h"

yapi::YAPI::YAPI()
{

}

yapi::YAPI::~YAPI()
{

}

void yapi::YAPI::RegisterPin(InputPin& pin)
{
  m_inputPinMap.insert({ pin.GetName(), pin });
  pin.SetSampleEventHandler(this);
}

void yapi::YAPI::RegisterPin(OutputPin& pin)
{
  m_outputPinMap.insert({ pin.GetName(), pin });
}

const yapi::YAPI::InputPinList& yapi::YAPI::GetInputPins() const
{
  return m_inputPinMap;
}

const yapi::YAPI::OutputPinList& yapi::YAPI::GetOutputPins() const
{
  return m_outputPinMap;
}

yapi::InputPin& yapi::YAPI::GetInputPin(const std::string& pinName)
{
  auto& it = m_inputPinMap.find(pinName);
  if (it == m_inputPinMap.end()) {
    throw std::exception("InputPin not found");
  }

  return it->second;
}

yapi::OutputPin& yapi::YAPI::GetOutputPin(const std::string& pinName)
{
  auto& it = m_outputPinMap.find(pinName);
  if (it == m_outputPinMap.end()) {
    throw std::exception("OutputPin not found");
  }

  return it->second;
}

void yapi::YAPI::Connect(const std::string& pinName, yapi::InputPin& inputPin)
{
  GetOutputPin(pinName).Connect(inputPin);
}

void yapi::YAPI::SetStartTime(const std::chrono::high_resolution_clock::time_point& startTime)
{
  m_startTime = startTime;
}

int64_t yapi::YAPI::GetTimeSinceStart() const
{
  const auto duration = std::chrono::high_resolution_clock::now() - m_startTime;
  return duration.count();
}

void yapi::Connect(YAPI* pluginSrc, const std::string& pinSrc, YAPI* pluginDst, const std::string& pinDst)
{
  pluginSrc->Connect(pinSrc, pluginDst->GetInputPin(pinDst));
}


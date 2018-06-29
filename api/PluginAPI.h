#ifndef PLUGIN_API
#define PLUGIN_API

#include <unordered_map>
#include <vector>
#include <string>
#include <exception>
#include <functional>

// yet another plugin API
namespace yapi
{
  class SampleEventHandler
  {
  public:
    virtual ~SampleEventHandler() {}
    virtual void SampleReceivedEvent(const std::string& pinName, const char*const buffer, const size_t bufferSize) = 0;
  };


  class InputPin
  {
  public:
    InputPin(const std::string& name)
    {
      m_name = name;
    }

    void SetSampleEventHandler(SampleEventHandler* event)
    {
      m_onPinEvent = event;
    }

    SampleEventHandler* GetSampleEventHandler()
    {
      if (m_onPinEvent == nullptr) {
        throw std::exception("SampleEventHandler is not set!");
      }

      return m_onPinEvent;
    }

    const std::string& GetName() const
    {
      return m_name;
    }

  private:
    SampleEventHandler * m_onPinEvent;
    std::string m_name;
  };


  class OutputPin
  {
  public:
    OutputPin(const std::string& name)
    {
      m_name = name;
    }

    void Connect(InputPin* pin)
    {
      m_inputPinList.push_back(pin);
    }

    void Transmit(const char*const buffer, const size_t bufferSize)
    {
      for (auto pin : m_inputPinList) {
        pin->GetSampleEventHandler()->SampleReceivedEvent(pin->GetName(), buffer, bufferSize);
      }
    }

    const std::string& GetName() const
    {
      return m_name;
    }

  private:
    std::string m_name;
    typedef std::vector<InputPin*> InputPinList;
    InputPinList m_inputPinList;
  };


  class YAPI : public SampleEventHandler
  {
  public:
    typedef std::unordered_map<std::string, InputPin*> InputPinList;
    typedef std::unordered_map<std::string, OutputPin*> OutputPinList;

  public:
    YAPI() {};
    virtual ~YAPI() {}

    void RegisterPin(InputPin& pin)
    {
      m_inputPinMap[pin.GetName()] = &pin;
      pin.SetSampleEventHandler(this);
    }

    void RegisterPin(OutputPin& pin)
    {
      m_outputPinMap[pin.GetName()] = &pin;
    }

    const InputPinList& GetInputPins() const
    {
      return m_inputPinMap;
    }

    const OutputPinList& GetOutputPins() const
    {
      return m_outputPinMap;
    }

    InputPin* GetInputPin(const std::string& pinName)
    {
      auto& it = m_inputPinMap.find(pinName);
      if (it == m_inputPinMap.end()) {
        throw std::exception("InputPin not found");
      }

      return it->second;
    }

    OutputPin* GetOutputPin(const std::string& pinName)
    {
      auto& it = m_outputPinMap.find(pinName);
      if (it == m_outputPinMap.end()) {
        throw std::exception("OutputPin not found");
      }

      return it->second;
    }

    void Connect(const std::string& pinName, InputPin* inputPin)
    {
      GetOutputPin(pinName)->Connect(inputPin);
    }

  public:
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual std::string GetPluginName() const = 0;

  private:
    InputPinList m_inputPinMap;
    OutputPinList m_outputPinMap;
  };
}

#define CREATE_PLUGIN(classname) \
  extern "C" { \
    __declspec(dllexport) classname* createPlugin() \
    { \
      return new classname(); \
    } \
  }

#endif
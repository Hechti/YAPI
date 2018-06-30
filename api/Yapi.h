#ifndef YAPI_YET_ANOTHER_PLUGIN_API
#define YAPI_YET_ANOTHER_PLUGIN_API

#include <unordered_map>
#include <vector>
#include <string>
#include <exception>
#include <functional>
#include <chrono>

#include "SampleEventHandler.h"
#include "InputPin.h"
#include "OutputPin.h"

// yet another plugin API
namespace yapi
{
  class YAPI : public SampleEventHandler
  {
  public:
    typedef std::unordered_map<std::string, InputPin*> InputPinList;
    typedef std::unordered_map<std::string, OutputPin*> OutputPinList;

  public:
    YAPI();
    virtual ~YAPI();

    void RegisterPin(InputPin& pin);
    void RegisterPin(OutputPin& pin);
    const InputPinList& GetInputPins() const;
    const OutputPinList& GetOutputPins() const;
    InputPin* GetInputPin(const std::string& pinName);
    OutputPin* GetOutputPin(const std::string& pinName);
    void Connect(const std::string& pinName, InputPin* inputPin);
    void SetStartTime(const std::chrono::high_resolution_clock::time_point& startTime);
    int64_t GetTimeSinceStart() const;

  public:
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual std::string GetPluginName() const = 0;

  private:
    InputPinList m_inputPinMap;
    OutputPinList m_outputPinMap;
    std::chrono::high_resolution_clock::time_point m_startTime;
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
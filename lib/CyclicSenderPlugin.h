#ifndef CYCLIC_SENDER_PLUGIN
#define CYCLIC_SENDER_PLUGIN

#include "CyclicPlugin.h"
using namespace yapi;

class CyclicSenderPlugin : public CyclicPlugin {
public:
    CyclicSenderPlugin();
    virtual ~CyclicSenderPlugin();

    virtual void SampleReceivedEvent(const std::string& pinName, const char*const buffer, const size_t bufferSize) override;
    virtual std::string GetPluginName() const override;
    void Cycle() override;

private:
    OutputPin m_pin;
    int m_value;
};

#endif
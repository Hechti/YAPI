#include "CyclicSenderPlugin.h"


CyclicSenderPlugin::CyclicSenderPlugin() : CyclicPlugin(std::chrono::milliseconds(100)), m_pin("Output"), m_value(1000)
{
    RegisterPin(m_pin);
}

CyclicSenderPlugin::~CyclicSenderPlugin()
{
}

void CyclicSenderPlugin::SampleReceivedEvent(const std::string & pinName, const char * const buffer, const size_t bufferSize)
{
}

std::string CyclicSenderPlugin::GetPluginName() const
{
    return "CyclicSenderPlugin";
}

void CyclicSenderPlugin::Cycle()
{
    m_pin.Transmit(reinterpret_cast<const char*const>(&m_value), sizeof(int));
    m_value++;
}



CREATE_PLUGIN(CyclicSenderPlugin)
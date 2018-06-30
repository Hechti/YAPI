#include "CyclicPlugin.h"

yapi::CyclicPlugin::CyclicPlugin() : m_stopThread(false), m_interval(0)
{

}

yapi::CyclicPlugin::CyclicPlugin(std::chrono::milliseconds interval) : m_stopThread(false), m_interval(interval)
{

}

yapi::CyclicPlugin::~CyclicPlugin()
{
  if (m_sendThread && m_sendThread->joinable()) {
    m_stopThread = true;
    m_sendThread->join();
  }
}

void yapi::CyclicPlugin::Start()
{
  m_sendThread.reset(
    new std::thread([this]() {
      while (!m_stopThread) {
        std::this_thread::sleep_for(m_interval);
        Cycle();
      }
    })
  );
}

void yapi::CyclicPlugin::Stop()
{
  if (m_sendThread && m_sendThread->joinable()) {
    m_stopThread = true;
    m_sendThread->join();
  }
}




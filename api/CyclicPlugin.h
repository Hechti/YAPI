#ifndef YAPI_CYCLIC_PLUGIN
#define YAPI_CYCLIC_PLUGIN

#include "Yapi.h"
#include <chrono>
#include <thread>
#include <atomic>

namespace yapi {
  class CyclicPlugin : public yapi::YAPI
  {

  public:
    CyclicPlugin();
    explicit CyclicPlugin(std::chrono::milliseconds interval);
    virtual ~CyclicPlugin();

  public:
    virtual void Start() override final;
    virtual void Stop() override final;

  public:
    virtual void Cycle() = 0;

  private:
    std::unique_ptr<std::thread> m_sendThread;
    std::atomic_bool m_stopThread;
    const std::chrono::milliseconds m_interval;
  };
}
#endif
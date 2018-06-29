#ifndef CYCLIC_PLUGIN
#define CYCLIC_PLUGIN

#include "PluginAPI.h"
#include <chrono>
#include <thread>
#include <atomic>

namespace yapi {
    class CyclicPlugin : public yapi::YAPI
    {

    public:
        CyclicPlugin() : m_stopThread(false), m_interval(0) {};
        explicit CyclicPlugin(std::chrono::milliseconds interval) : m_stopThread(false), m_interval(interval) {};
        virtual ~CyclicPlugin() {};
    public:
        virtual void SampleReceivedEvent(const std::string& pinName, const char*const buffer, const size_t bufferSize) = 0;
        virtual void Start() override final {
            m_sendThread.reset(new std::thread([this]() {
                while (!m_stopThread) {
                    std::this_thread::sleep_for(m_interval);
                    Cycle();
                };
            }
            )
            );

        };
        virtual void Stop() override final{

            if (m_sendThread && m_sendThread->joinable()) {
                m_stopThread = true;
                m_sendThread->join();
            }
        };
        virtual std::string GetPluginName() const = 0;

        virtual void Cycle() = 0;

    private:
        std::unique_ptr<std::thread> m_sendThread;
        std::atomic_bool m_stopThread;
        const std::chrono::milliseconds m_interval;

    };
}
#endif
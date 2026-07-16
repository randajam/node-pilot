# pragma once

#include <atomic>
#include "MetricsCollector.hpp"
#include "ITransport.hpp"

class Agent {
private:
    std::atomic<bool>& m_running;
    MetricsCollector m_metrics;
    transport::ITransport& m_transport;
    int m_interval;
public:
    explicit Agent(std::atomic<bool>& running, transport::ITransport& transport, int interval);

    void start();
    void loop();
    void stop();

    void update();
    void sleep(int seconds = 1) const;
    void publishMetrics(const SystemMetrics&);
};
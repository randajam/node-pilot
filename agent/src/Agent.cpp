#include "Agent.hpp"
#include "ITransport.hpp"
#include "MetricsCollector.hpp"
#include "Logger.hpp"
#include "JsonSerializer.hpp"
#include "MetricsMessage.hpp"
#include <thread>
#include <atomic>

Agent::Agent(std::atomic<bool>& running, transport::ITransport& transport, int interval): m_running(running), m_transport(transport), m_interval(interval) {}

void Agent::start() {
    logging::log("Agent started", LogLevel::Info, LogCategory::General);
}

void Agent::loop() {
    while (m_running.load()) {
        update();
        sleep(m_interval);
    }
}

void Agent::stop() {
    logging::log("Agent stopped", LogLevel::Info, LogCategory::General);
}

void Agent::update() {
    SystemMetrics metrics = m_metrics.collect();
    publishMetrics(metrics);
}

void Agent::publishMetrics(const SystemMetrics& metrics) {
    // Собираем сообщение
    std::uint64_t now = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
    
    protocol::MetricsMessage msg {"METRICS", metrics, now};
    
    // Сериализируем в json формат
    auto json = protocol::serialize(msg);

    // Отправляем
    m_transport.send(json);
}

void Agent::sleep(int seconds) const {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}
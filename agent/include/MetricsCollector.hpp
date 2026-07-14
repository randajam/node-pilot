#pragma once

#include <cstdint>

struct SystemMetrics {
    double uptime;
    double cpuUsage;
    std::uint64_t ramTotal;
    std::uint64_t ramUsed;
    double diskUsage;
};

struct MemInfo {
    std::uint64_t ramTotal;
    std::uint64_t ramAvailable;
};

struct CpuTimes
{
    std::uint64_t user;
    std::uint64_t nice;
    std::uint64_t system;
    std::uint64_t idle;
    std::uint64_t iowait;
    std::uint64_t irq;
    std::uint64_t softirq;
    std::uint64_t steal;
};

class MetricsCollector {
public:
    SystemMetrics collect();
private:
    double getUptime() const;

    CpuTimes m_previousCpuTimes{};
    bool m_cpuInitialized{false};
    CpuTimes getCpuTimes() const;
    double getCpuUsage();
    
    MemInfo getMemInfo() const;
    double getDiskUsage() const;
};
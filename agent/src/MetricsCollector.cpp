#include "MetricsCollector.hpp"

#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <sys/statvfs.h>

double MetricsCollector::getUptime() const {
    std::ifstream file("/proc/uptime");
    
    if (!file) {
        throw std::runtime_error("Can not open /proc/uptime");
    }

    double uptime;

    file >> uptime;

    return uptime;
}

CpuTimes MetricsCollector::getCpuTimes() const {
    CpuTimes new_times;

    std::ifstream file("/proc/stat");
    
    if (!file) {
        throw std::runtime_error("Can not open /proc/stat");
    }

    std::string line, key;
    std::getline(file, line);
    
    std::istringstream iss(line);

    iss >> key >> new_times.user >> new_times.nice 
    >> new_times.system >> new_times.idle 
    >> new_times.iowait >> new_times.irq 
    >> new_times.softirq >> new_times.steal;

    return new_times;
}

double MetricsCollector::getCpuUsage() {
    if (!m_cpuInitialized) {
        m_previousCpuTimes = getCpuTimes();
        m_cpuInitialized = true;
        return 0;
    }
    std::uint64_t Idle{}, Total{};
    CpuTimes new_times = getCpuTimes();

    Idle = new_times.idle + new_times.iowait;
    Total = new_times.user + new_times.nice + new_times.idle + new_times.iowait
    + new_times.system + new_times.irq + new_times.softirq + new_times.steal;

    Idle -= m_previousCpuTimes.idle + m_previousCpuTimes.iowait;
    Total -= m_previousCpuTimes.user + m_previousCpuTimes.nice + m_previousCpuTimes.idle + m_previousCpuTimes.iowait
    + m_previousCpuTimes.system + m_previousCpuTimes.irq + m_previousCpuTimes.softirq + m_previousCpuTimes.steal;
    
    if (Total == 0) {
        return 0;
    }

    m_previousCpuTimes = new_times;

    return 100.0 * (Total - Idle) / Total;
}

MemInfo MetricsCollector::getMemInfo() const {
    std::ifstream file("/proc/meminfo");
    
    if (!file) {
        throw std::runtime_error("Can not open /proc/meminfo");
    }

    MemInfo info{};

    std::string line;

    while (std::getline(file, line)) {
        std::string key;
        std::uint64_t value;
        std::string unit;

        std::istringstream iss(line);

        iss >> key >> value >> unit;

        if (key == "MemTotal:") {
            info.ramTotal = value;
        } else if (key == "MemAvailable:") {
            info.ramAvailable = value;
        }
    }

    return info;
}

double MetricsCollector::getDiskUsage() const
{
    // Структура, которую заполнит ядро Linux
    struct statvfs fs{};

    // Получаем информацию о файловой системе,
    // на которой находится корень "/"
    if (statvfs("/", &fs) != 0) {
        throw std::runtime_error("Cannot get filesystem statistics");
    }

    // Общее количество байт
    std::uint64_t totalBytes =
        static_cast<std::uint64_t>(fs.f_blocks) * fs.f_frsize;

    // Количество байт, доступных обычному пользователю
    std::uint64_t availableBytes =
        static_cast<std::uint64_t>(fs.f_bavail) * fs.f_frsize;

    // Использовано байт
    std::uint64_t usedBytes =
        totalBytes - availableBytes;

    // Защита от деления на ноль
    if (totalBytes == 0) {
        return 0.0;
    }

    // Процент использования
    return static_cast<double>(usedBytes) /
           static_cast<double>(totalBytes) * 100.0;
}

SystemMetrics MetricsCollector::collect() {
    MemInfo meminfo = getMemInfo();
    return {getUptime(),
    getCpuUsage(),
    meminfo.ramTotal,
    meminfo.ramTotal - meminfo.ramAvailable,
    getDiskUsage()
    };
}
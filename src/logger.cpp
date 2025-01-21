#include "logger.h"
#include <iostream>


Logger::Logger(const std::string& filename, LogLevel defaultLevel) : filename_(filename), defaultLevel_(defaultLevel) {
    logFile_.open(filename_, std::ios::app);
    if (!logFile_.is_open()) {
        std::cerr << "Error opening log file: " << filename_ << std::endl;
    }
}

Logger::~Logger() {
    if (logFile_.is_open()) {
        logFile_.close();
    }
}

void Logger::log(const std::string& message, LogLevel level) {
    if (level >= defaultLevel_ && logFile_.is_open()) {
        std::lock_guard<std::mutex> lock(logMutex_);
        logFile_ << getCurrentTimestamp() << " [" << levelToString(level) << "] " << message << std::endl;
    }
}

void Logger::setDefaultLevel(LogLevel level) {
    defaultLevel_ = level;
}

LogLevel Logger::getDefaultLevel() const {
    return defaultLevel_;
}


std::string Logger::levelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO:  return "INFO";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

std::string Logger::getCurrentTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm;
    localtime_r(&now_c, &now_tm);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &now_tm);
    return buffer;
}
#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <chrono>
#include <fstream>
#include <mutex>
#include <iostream>


enum class LogLevel {
    DEBUG,
    INFO,
    ERROR
};

class Logger {
public:
    Logger(const std::string& filename, LogLevel defaultLevel = LogLevel::INFO);
    ~Logger();
    void log(const std::string& message, LogLevel level);
    void setDefaultLevel(LogLevel level);
    LogLevel getDefaultLevel() const;
    
private:
    std::string filename_;
    LogLevel defaultLevel_;
    std::ofstream logFile_;
    std::mutex logMutex_;
    
    std::string levelToString(LogLevel level) const;
    std::string getCurrentTimestamp() const;
};

#endif
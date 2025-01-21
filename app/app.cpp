#include "../include/logger.h"
#include <iostream>
#include <string>
#include <thread>
#include <sstream>
#include <functional>

// Функция для преобразования строки в LogLevel
LogLevel parseLogLevel(const std::string& levelStr) {
    if (levelStr == "DEBUG") return LogLevel::DEBUG;
    if (levelStr == "INFO") return LogLevel::INFO;
    if (levelStr == "ERROR") return LogLevel::ERROR;
    return LogLevel::INFO; // По умолчанию INFO, если строка не распознана
}

int main(int argc, char* argv[]) {
    // Проверка аргументов командной строки
    if (argc < 3) {
        std::cerr << "Usage: app <log_file> <default_log_level> \nExample: app mylog.txt INFO" << std::endl;
        return 1;
    }

    std::string logFilename = argv[1]; // Получаем имя файла из аргументов
    LogLevel defaultLevel = parseLogLevel(argv[2]); // Получаем уровень по умолчанию из аргументов

    Logger logger(logFilename, defaultLevel); // Создаем объект логгера
    
    std::string input;
    
    // Лямбда-функция для записи сообщения в лог (для передачи в поток)
    std::function<void(const std::string&, LogLevel)> logMessage = 
        [&](const std::string& message, LogLevel level) {
            logger.log(message, level);
    };
        
    // Основной цикл приема ввода от пользователя
    while (true) {
        std::cout << "Enter message (or 'exit' to quit):" << std::endl;
        std::getline(std::cin, input); // Получаем ввод от пользователя
        if (input == "exit") break; // Выход из цикла

        std::string levelStr;
        std::cout << "Enter level (DEBUG, INFO, ERROR, or leave empty for default):" << std::endl;
        std::getline(std::cin, levelStr); // Получаем уровень из ввода пользователя
        
        LogLevel messageLevel = defaultLevel;
        if (!levelStr.empty()) {
            messageLevel = parseLogLevel(levelStr); // Парсим введенный уровень
        }

        
        // Создаем новый поток для записи сообщения в лог
        std::thread logThread(logMessage, input, messageLevel);
        logThread.detach(); // Отсоединяем поток, чтобы он выполнялся независимо
    }
    return 0;
}
#include "../../headers/system/Logger.h"
#include <iostream>
#include <ctime>

Logger* Logger::instance = nullptr;

Logger::Logger()
    : logFilePath("log.txt")
{
}

Logger::~Logger()
{
}

Logger* Logger::getInstance()
{
    if (instance == nullptr) {
        instance = new Logger();
    }
    return instance;
}

void Logger::log(const std::string& event)
{
    std::ofstream logFile(logFilePath, std::ios::app);

    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file" << std::endl;
        return;
    }

    logFile << event << std::endl;
    logFile.close();
}


#include "../../headers/system/Logger.h"
#include "../../headers/exceptions/FileExceptionIn.h"
#include <iostream>
#include <ctime>

Logger::Logger()
    : logFilePath("../log.txt")
{
}

Logger* Logger::getInstance() {
    static Logger instance;
    return &instance;
}

void Logger::log(const std::string& event)
{
    std::ofstream logFile(logFilePath, std::ios::app);

    if (!logFile.is_open()) {
        throw(FileExceptionIn("Could not open log file for writing."));
    }

    logFile << event << std::endl;
    logFile.close();
}

void Logger::log(const std::string& event,const std::string& otherLogPath)
{
    std::ofstream logFile(otherLogPath, std::ios::app);

    if (!logFile.is_open()) {
        throw(FileExceptionIn("Could not open log file for writing."));
    }

    logFile << event << std::endl;
    logFile.close();
}
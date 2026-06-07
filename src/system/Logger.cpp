#include "../../headers/system/Logger.h"
#include "../../headers/exceptions/ErrorArchivoLectura.h"
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
        throw(ErrorArchivoLectura("Could not open log file for writing."));
    }

    logFile << event << std::endl;
    logFile.close();
}


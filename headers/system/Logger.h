#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>


class Logger // Singleton
{
private:
    static Logger* instance;
    std::string logFilePath;

    Logger();

public:
    ~Logger();

    static Logger* getInstance();

    void log(const std::string& event);

    // Delete copy constructor and assignment operator
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

#endif

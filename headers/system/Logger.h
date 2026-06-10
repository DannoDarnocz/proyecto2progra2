#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <memory>


class Logger // Singleton returns pointer to the instance that is actually just a local static object to avoid memory leaks, instead of using a single instance that is stored as member of static
{
private:
    std::string logFilePath;
    Logger();
public:

    static  Logger* getInstance();

    void log(const std::string& event);
    void log(const std::string& event,const std::string&); // different route
};

#endif

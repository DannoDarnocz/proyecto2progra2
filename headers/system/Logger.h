#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <memory>
#include <sstream>


class Logger // Singleton returns pointer to the instance that is actually just a local static object to avoid memory leaks, instead of using a single instance that is stored as member of static
{
private:
    std::string logFilePath;
    Logger();
public:

    static  Logger* getInstance();

    void log(const std::string& event);
    void log(const std::string& event,const std::string&); // different route
    void exportReport(
        const std::string& playerInfo,
        const std::string& route,
        bool outcome = false,
        int level = 1,
        int indexDimension = 0,
        int totalKills = 0,
        int totalEscapes = 0,
        int damageDealt = 0,
        int damageTaken = 0,
        int bossesKilled = 0,
        int debuffApplied = 0,
        int cellVisited = 0,
        int cellDug = 0,
        int bombExploded = 0,
        int medkitFound = 0,
        int powerUpCollected = 0); //Write Report
};

#endif

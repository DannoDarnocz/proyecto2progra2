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

void Logger::log(const std::string& event,const std::string& otherLogPath) //Delete and creates a new one
{
    std::ofstream logFile(otherLogPath, std::ios::trunc);

    if (!logFile.is_open()) {
        throw(FileExceptionIn("Could not open log file for writing."));
    }

    logFile << event;
    logFile.close();
}

void Logger::exportReport(const std::string& event, const std::string& otherLogPath, bool outcome,
        int level, int indexDimension, int totalKills, int totalEscapes, int damageDealt,
        int damageTaken, int bossesKilled, int debuffApplied, int cellVisited, int cellDug,
        int bombExploded, int medkitFound, int powerUpCollected)
{
    stringstream s;

    s << "\n========================================\n";
    s << "      BLOCK WORLD - FINAL REPORT\n";
    s << "========================================\n";

    s << "\n[SESSION INFO]\n";
    s << "----------------------------------------\n";
    s << event << "\n";
    s << "Full log available at: log.txt\n";

    s << "\n[FINAL RESULT]\n";
    s << "----------------------------------------\n";
    s << "Outcome:       " << (outcome ? "VICTORY" : "DEFEAT") << "\n";
    s << "Level reached: " << level << "\n";
    s << "Dimension:     " << indexDimension + 1 << "\n";

    s << "\n[COMBAT STATS]\n";
    s << "----------------------------------------\n";
    s << "Monsters killed:  " << totalKills << "\n";
    s << "Times escaped:    " << totalEscapes << "\n";
    s << "Bosses defeated:  " << bossesKilled << "\n";
    s << "Debuffs received: " << debuffApplied << "\n";
    s << "Damage dealt:     " << damageDealt << "\n";
    s << "Damage taken:     " << damageTaken << "\n";

    s << "\n[EXPLORATION STATS]\n";
    s << "----------------------------------------\n";
    s << "Cells visited:    " << cellVisited << "\n";
    s << "Cells dug:        " << cellDug << "\n";
    s << "Bombs exploded:   " << bombExploded << "\n";
    s << "Medkits found:    " << medkitFound << "\n";
    s << "Power-ups collected: " << powerUpCollected << "\n";

    s << "\n[PROGRESSION]\n";
    s << "----------------------------------------\n";
    s << "Final level:      " << level << "\n";
    s << "Dimension reached: " << indexDimension + 1 << "\n";
    s << "Dimensions cleared: " << (outcome ? indexDimension + 1 : indexDimension) << "\n";
    s << "Map cleared: " << (outcome ? "Yes" : "No") << "\n";

    s << "\n========================================\n\n";

    std::ofstream logFile(otherLogPath, std::ios::app);

    if (!logFile.is_open()) {
        throw(FileExceptionIn("Could not open log file for writing."));
    }

    logFile << s.str() << std::endl;
    logFile.close();

    log(s.str(),"../final_report_only_current_session.txt");
}

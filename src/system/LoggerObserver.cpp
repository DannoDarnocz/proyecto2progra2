#include "../../headers/system/LoggerObserver.h"
#include "../../headers/system/Logger.h"
#include "../../headers/player/Player.h"
#include <sstream>

LoggerObserver::LoggerObserver()
{
}

LoggerObserver::~LoggerObserver()
{
}

void LoggerObserver::onLevelUp(Player& player)
{
    // Log level up event
    std::ostringstream oss;
    oss << "Player leveled up to level " << player.getLevel();
    Logger::getInstance()->log(oss.str());
}


#ifndef LOGGEROBSERVER_H
#define LOGGEROBSERVER_H

#include "EventObserver.h"

class LoggerObserver : public EventObserver
{
public:
    LoggerObserver();
    virtual ~LoggerObserver();

    virtual void onLevelUp(Player& player) override;
};

#endif

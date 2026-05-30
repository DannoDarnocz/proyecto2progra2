#ifndef EVENTOBSERVER_H
#define EVENTOBSERVER_H

#include <string>

class Player;

class EventObserver
{
public:
    EventObserver();
    virtual ~EventObserver();

    virtual void onLevelUp(Player& player) = 0;
};

#endif

#ifndef MAPOBSERVER_H
#define MAPOBSERVER_H

#include "EventObserver.h"

class Map;

class MapObserver : public EventObserver
{
private:
    Map* map;

public:
    MapObserver(Map* map);
    virtual ~MapObserver();

    virtual void onLevelUp(Player& player) override;
};

#endif

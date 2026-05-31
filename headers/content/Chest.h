#ifndef CHEST_H
#define CHEST_H

#include "Content.h"
#include <vector>

class Player;
//class Item;

class Chest : public Content
{
private:
    //std::vector<Item*> items;

public:
    Chest();
    virtual ~Chest();

    //void addItem(Item* item);
    //void removeItem(Item* item);
    //const std::vector<Item*>& getItems() const;

    virtual void interact(Player& player) override;
};

#endif

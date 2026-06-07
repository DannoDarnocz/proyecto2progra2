#ifndef CONTENT_H
#define CONTENT_H
#include <string>

class Player;

class Content
{
protected:
    bool visible;
    bool consumable; // destroy after interactions
public:
    Content(bool = true, bool = false);
    virtual ~Content();

    bool isVisible() const;
    void setVisible(bool visible);

    bool isConsumable() const;

    virtual std::string toString() = 0;

    // Returns: 0 if not consumable, 1 if consumable, 2 if monster
    virtual int interact(Player& player) = 0;
};

#endif

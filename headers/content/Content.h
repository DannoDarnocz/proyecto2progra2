#ifndef CONTENT_H
#define CONTENT_H
#include <string>

class Player;

enum class ContentType
{
    BOMB,
    MEDKIT,
    POWERUP,
    MONSTER
};

enum class InteractResult
{
    NOTHING,       // nothing was here
    NOT_CONSUMABLE, // interacted, but content stays (e.g. defeated monster, dug-out bomb)
    CONSUMABLE,    // interacted, content should be removed from the cell
    MONSTER        // content is a live monster, combat should start
};

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

    virtual ContentType getContentType() const = 0;

    // Returns: 0 if not consumable, 1 if consumable, 2 if monster
    virtual InteractResult interact(Player& player) = 0;
};

#endif

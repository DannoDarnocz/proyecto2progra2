#ifndef CONTENT_H
#define CONTENT_H
#include <string>

class Player;

class Content
{
protected:
    bool visible;

public:
    Content(bool = true);
    virtual ~Content();

    bool isVisible() const;
    void setVisible(bool visible);

    virtual std::string toString() = 0;

    virtual void interact(Player& player) = 0;
};

#endif

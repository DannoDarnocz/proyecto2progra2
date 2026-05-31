#ifndef CONTENT_H
#define CONTENT_H

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

    virtual void interact(Player& player) = 0;
};

#endif

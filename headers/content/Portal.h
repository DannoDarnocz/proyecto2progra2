#ifndef PORTAL_H
#define PORTAL_H

#include "Content.h"

class Dimension;

class Portal : public Content
{
private:
    Dimension* targetDimension;
    bool requiresKey;

public:
    Portal(Dimension* target, bool requiresKey = false);
    virtual ~Portal();

    Dimension* getTargetDimension() const;
    void setTargetDimension(Dimension* dimension);

    bool isKeyRequired() const;
    void setKeyRequired(bool required);

    virtual void interact(Player& player) override;
};

#endif

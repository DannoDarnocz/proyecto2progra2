#include "../../headers/content/Content.h"

Content::Content(bool isVisible, bool isConsumable)
    : visible(isVisible),consumable(isConsumable)
{
}

Content::~Content()
{
}

bool Content::isVisible() const
{
    return visible;
}

void Content::setVisible(bool visible)
{
    this->visible = visible;
}
bool Content::isConsumable() const
{
    return consumable;
}

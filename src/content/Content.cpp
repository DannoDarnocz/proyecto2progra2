#include "../../headers/content/Content.h"

Content::Content()
    : visible(true)
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


#include "../../headers/content/Portal.h"
#include "../../headers/player/Player.h"

Portal::Portal(Dimension* target, bool requiresKey)
    : targetDimension(target), requiresKey(requiresKey)
{
}

Portal::~Portal()
{
}

Dimension* Portal::getTargetDimension() const
{
    return targetDimension;
}

void Portal::setTargetDimension(Dimension* dimension)
{
    targetDimension = dimension;
}

bool Portal::isKeyRequired() const
{
    return requiresKey;
}

void Portal::setKeyRequired(bool required)
{
    requiresKey = required;
}

void Portal::interact(Player& player)
{
    // Teleport player to target dimension if conditions are met
    if (requiresKey && !player.hasKeyItem()) {
        // Cannot teleport without key
        return;
    }

    // Teleport logic would go here
}


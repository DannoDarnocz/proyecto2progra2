#include "../../headers/world/Map.h"

Map::Map()
    : currentDimensionIndex(0)
{
}

Map::~Map()
{
    // no destructor required due to unique_ptr
}

void Map::addDimension(std::unique_ptr<Dimension> dimension)
{
    if (dimension != nullptr) {
        dimensions.push_back(std::move(dimension));
    }
}

Dimension* Map::getCurrentDimension() const
{
    if (currentDimensionIndex >= 0 && currentDimensionIndex < (int)dimensions.size()) {
        return dimensions[currentDimensionIndex].get();
    }
    return nullptr;
}

Dimension* Map::getDimension(int index) const
{
    if (index >= 0 && index < (int)dimensions.size()) {
        return dimensions[index].get();
    }
    return nullptr;
}

int Map::getCurrentDimensionIndex() const
{
    return currentDimensionIndex;
}

void Map::setCurrentDimensionIndex(int index)
{
    if (index >= 0 && index < (int)dimensions.size()) {
        currentDimensionIndex = index;
    }
}

void Map::changeDimension(int index)
{
    setCurrentDimensionIndex(index);
}

int Map::getDimensionCount() const
{
    return (int)dimensions.size();
}

void Map::releaseDimension(int index) {
    if (index >= 0 && index < (int)dimensions.size() && dimensions[index] != nullptr) {
        dimensions[index] = nullptr;
    }
}

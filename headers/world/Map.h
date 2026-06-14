#ifndef MAP_H
#define MAP_H

#include <memory>

#include "Dimension.h"
#include <vector>

class Map
{
private:
    std::vector<std::unique_ptr<Dimension>> dimensions;
    int currentDimensionIndex;

public:
    Map();
    ~Map();

    void addDimension(std::unique_ptr<Dimension> dimension);
    Dimension* getCurrentDimension() const;
    Dimension* getDimension(int index) const;

    int getCurrentDimensionIndex() const;
    void setCurrentDimensionIndex(int index);

    void changeDimension(int index);
    void releaseDimension(int index);
    int getDimensionCount() const;
};

#endif

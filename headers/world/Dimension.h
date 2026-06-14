#ifndef DIMENSION_H
#define DIMENSION_H

#include "../content/Content.h"
#include <vector>

class Cell;

class Dimension
{
private:
    std::vector<std::vector<Cell*>> matrix;
    int rows;
    int cols;

public:
    Dimension(int rows, int cols);
    ~Dimension();

    Cell* getCell(int x, int y);
    void setCell(int x, int y, Cell* cell);


    int getRows() const;
    int getCols() const;
};

#endif

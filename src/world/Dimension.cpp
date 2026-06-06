#include "../../headers/world/Dimension.h"
#include "../../headers/world/Cell.h"

Dimension::Dimension(int rows, int cols)
    : rows(rows), cols(cols), boss(nullptr)
{
    matrix.resize(rows);
    for (int i = 0; i < rows; ++i) {
        matrix[i].resize(cols, nullptr);
    }
}

Dimension::~Dimension()
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            delete matrix[i][j];
        }
    }
}

Cell* Dimension::getCell(int x, int y)
{
    if (x >= 0 && x < rows && y >= 0 && y < cols) {
        return matrix[x][y];
    }
    return nullptr;
}

void Dimension::setCell(int x, int y, Cell* cell)
{
    if (x >= 0 && x < rows && y >= 0 && y < cols) {
        matrix[x][y] = cell;
    }
}

Content* Dimension::getBoss() const
{
    return boss;
}

void Dimension::setBoss(Content* boss)
{
    this->boss = boss;
}


int Dimension::getRows() const
{
    return rows;
}

int Dimension::getCols() const
{
    return cols;
}


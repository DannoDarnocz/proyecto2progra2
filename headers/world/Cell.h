#ifndef CELL_H
#define CELL_H
#include <memory>

#include "../content/Content.h"

class Player;
class Content;

enum class CellState
{
    UNEXPLORED,
    EXPLORED,
    DUG
};

class Cell
{
private:
    std::unique_ptr<Content> content;
    CellState state;

public:
    Cell(std::unique_ptr<Content> content = nullptr, CellState = CellState::UNEXPLORED); // if nullptr, nothing is in the cell
    ~Cell();

    Content* getContent() const;
    void setContent(std::unique_ptr<Content> content);

    CellState getState() const;
    void setState(CellState state);

    InteractResult interact(Player& player, int& amountPowerUps);
    void dig(Player& player, int& amountDug, int& medkitFound, int& bombFound);
};

#endif

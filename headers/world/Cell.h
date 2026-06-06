#ifndef CELL_H
#define CELL_H
#include <memory>

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

    void interact(Player& player);
    void dig(Player& player);
};

#endif

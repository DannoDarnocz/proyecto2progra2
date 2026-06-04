#ifndef CELL_H
#define CELL_H

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
    Content& content;
    CellState state;

public:
    Cell(Content&, CellState = CellState::UNEXPLORED); // if nullptr, nothing is in the cell
    ~Cell();

    Content& getContent() const;
    void setContent(Content& content);

    CellState getState() const;
    void setState(CellState state);

    void interact(Player& player);
    void dig(Player& player);
};

#endif

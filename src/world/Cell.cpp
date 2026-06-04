#include "../../headers/world/Cell.h"

#include <iostream>

#include "../../headers/player/Player.h"
#include "../../headers/content/Content.h"

Cell::Cell(Content& content, CellState state)
    : content(content), state(state)
{
}

Cell::~Cell()
{
}

Content& Cell::getContent() const
{
    return content;
}

void Cell::setContent(Content& content)
{
    this->content = content;
}

CellState Cell::getState() const
{
    return state;
}

void Cell::setState(CellState state)
{
    this->state = state;
}

void Cell::interact(Player& player)
{
    // if not visible, don't interact yet
    if (content.isVisible()) {
        content.interact(player);
    }
}

void Cell::dig(Player& player)
{
    // Implementation for digging a cell
    if (state == CellState::UNEXPLORED) {
        state = CellState::DUG;
        content->interact(player);
    }
    else if (state == CellState::DUG)
    {
        std::cout << "But you find out you already dug here.";
    }
}


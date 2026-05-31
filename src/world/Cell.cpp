#include "../../headers/world/Cell.h"
#include "../../headers/player/Player.h"
#include "../../headers/content/Content.h"

Cell::Cell()
    : content(nullptr), state(CellState::UNEXPLORED)
{
}

Cell::~Cell()
{
    delete content;
}

Content* Cell::getContent() const
{
    return content;
}

void Cell::setContent(Content* content)
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
    if (content != nullptr) {
        content->interact(player);
    }
}

void Cell::dig(Player& player)
{
    // Implementation for digging a cell

}


#include "../../headers/world/Cell.h"

#include <iostream>

#include "../../headers/player/Player.h"
#include "../../headers/content/Content.h"

Cell::Cell(std::unique_ptr<Content> content, CellState state)
    : content(std::move(content)), state(state)
{
}

Cell::~Cell()
{
}

Content* Cell::getContent() const
{
    return content.get();
}

void Cell::setContent(std::unique_ptr<Content> newContent)
{
    // deletes if nullptr
    this->content = std::move(newContent);
}

CellState Cell::getState() const
{
    return state;
}

void Cell::setState(CellState state)
{
    this->state = state;
}

// boolean returns true if content should be destroyed after being used
int Cell::interact(Player& player)
{
    // If content is empty, it can search anything
    if (content == nullptr) {
        std::cout << "Nothing here.\n"; return -1;
    }
    // if not visible, don't interact yet
    if (content->isVisible()) {
        return content->interact(player);
    }
}

void Cell::dig(Player& player)
{
    // Implementation for digging a cell
    if (state == CellState::UNEXPLORED || state == CellState::EXPLORED) {
        state = CellState::DUG;
        if (content==nullptr) {
            std::cout << "You dig but find nothing.\n";
        }else {
            content->interact(player);
        }
    }
    else if (state == CellState::DUG)
    {
        std::cout << "But you find out you already dug here.";
    }
}


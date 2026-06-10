#include "../../headers/world/Cell.h"
#include "../../headers/system/Logger.h"
#include "../../headers/exceptions/FileException.h"

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

// boolean returns whatever content throws when interacting (should be destroyed after being used)
int Cell::interact(Player& player)
{
    // if it has something and it's visible, interact right away
    if (content && content->isVisible()) {
        return content->interact(player);
    }

    std::cout << "Nothing here.\n";
    Logger* logger = Logger::getInstance();
    try
    {
        logger->log("Found nothing.");
    }
    catch (ErrorArchivo& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return -1;
}

void Cell::dig(Player& player)
{
    Logger* logger = Logger::getInstance();
    // Implementation for digging a cell
    if (state == CellState::UNEXPLORED || state == CellState::EXPLORED) {
        state = CellState::DUG;
        if (content==nullptr) {
            std::cout << "You dig but find nothing.\n";
            try
            {
                logger->log("Dug but found nothing.");
            }
            catch (ErrorArchivo& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }else {
            content->interact(player);
        }
    }
    else if (state == CellState::DUG)
    {
        std::cout << "But you find out you already dug here.";
    }
}


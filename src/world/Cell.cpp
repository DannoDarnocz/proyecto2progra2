#include "../../headers/world/Cell.h"
#include "../../headers/system/Logger.h"
#include "../../headers/exceptions/FileException.h"

#include <iostream>

#include "../../headers/player/Player.h"
#include "../../headers/content/Content.h"
#include "../../headers/system/GameHelper.h"

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

//int return value when interacting with the content {0=NotConsumable,1=Consumable,2=Monster}
InteractResult Cell::interact(Player& player, int& amountPowerUps)
{
    // if it has something and it's visible, interact right away
    if (content && content->isVisible()) {
        if (content->getContentType() == ContentType::POWERUP) { amountPowerUps++; }
        return content->interact(player);
    }

    std::cout << "Nothing here.\n";
    GameHelper::safelog("Found nothing.");
    return InteractResult::NOTHING;
}

void Cell::dig(Player& player, int& amountDug, int& medkitFound, int& bombFound)
{
    Logger* logger = Logger::getInstance();
    // Implementation for digging a cell
    if (state == CellState::UNEXPLORED || state == CellState::EXPLORED) {
        state = CellState::DUG;
        amountDug++;
        if (content==nullptr) {
            std::cout << "You dig but find nothing.\n";
            GameHelper::safelog("Dug but found nothing.");
        }else {
            content->interact(player);
            if (content->getContentType() == ContentType::BOMB) { bombFound++; }
            if (content->getContentType() == ContentType::MEDKIT) { medkitFound++; }
        }
    }
    else if (state == CellState::DUG)
    {
        std::cout << "But you find out you already dug here.";
    }
}


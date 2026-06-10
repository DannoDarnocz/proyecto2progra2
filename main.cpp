#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cctype>
#include <limits>
#include <memory>
#include <thread>

#include "headers/system/GameHelper.h"
#include "headers/content/Bomb.h"
#include "headers/content/Medkit.h"
#include "headers/world/Map.h"
#include "headers/world/Dimension.h"
#include "headers/world/Cell.h"
#include "headers/player/Player.h"
#include "headers/content/Monster.h"
#include "headers/exceptions/FileException.h"
#include "headers/strategies/HealthLockAttack.h"
#include "headers/strategies/NormalAttack.h"
#include "headers/strategies/WeakenerAttack.h"
#include "headers/system/Logger.h"

using namespace std;



int main()
{
    srand(time(NULL));

    // Load map from files
    Map* gameMap = GameHelper::loadMapFromFiles("../map_data.txt");

    // Check if map was loaded successfully
    if (!gameMap || gameMap->getDimensionCount() == 0)
    {
        cerr << "Failed to load map from files. Exiting." << endl;
        return 1;
    }

    // Create player at starting position (0, 0) in first dimension
    unique_ptr<Player> player = make_unique<Player>(100,1);
    int currentX = 0;
    int currentY = 0;

    Dimension* currentDimension = gameMap->getCurrentDimension();

    // Validate starting position
    if (!currentDimension || !currentDimension->getCell(currentX, currentY))
    {
        cerr << "Invalid starting position. Exiting." << endl;
        return 1;
    }

    // Create logger
    Logger* logger = Logger::getInstance();
    try
    {
        logger->log("\n --- New game started ---");
    }
    catch (ErrorArchivo& e)
    {
        std::cerr << e.what() << endl;
    }

    cout << "====== BLOCK WORLD ======" << endl;
    cout << "Welcome, adventurer!" << endl << endl;


    bool gameRunning = true;

    // Main game loop
    while (gameRunning)
    {
        // Display current state
        GameHelper::displayMap(currentDimension, currentX, currentY);
        GameHelper::displayGameState(*player, currentX, currentY, currentDimension);

        // Get player input
        char input = static_cast<char>(tolower(GameHelper::getPlayerInput()));

        // stores cell that player moves to
        Cell* newCell = nullptr;
        string moveDirection;

        // move player, dig or quit
        switch (input)
        {
            case 'w':
                // Move up (decrease X) {Rows are X}
                if (currentX > 0){
                    currentX--;
                    moveDirection="up";
                }
                else{
                    cout << "\n> You cannot move further up. You are at the boundary." << endl;

                    continue;
                }
                break;

            case 'a':
                // Move left (decrease Y) {Columns are Y}
                if (currentY > 0) {
                    currentY--;
                    moveDirection="left";
                } else {
                    cout << "\n> You cannot move further left. You are at the boundary." << endl;
                    continue;
                }
                break;

            case 's':
                // Move down (increase X) {Rows are X}
                if (currentX < currentDimension->getRows() - 1){
                    currentX++;
                    moveDirection="down";
                } else {
                    cout << "\n> You cannot move further down. You are at the boundary." << endl;

                    continue;
                }
                break;

            case 'd':
                // Move right (increase Y) {Columns are Y}
                if (currentY < currentDimension->getCols() - 1){
                    currentY++;
                    moveDirection="right";
                } else{
                    cout << "\n> You cannot move further right. You are at the boundary." << endl;
                    continue;
                }
                break;
            case 'e':
                // Dig current cell
                {
                    Cell* currentCell = currentDimension->getCell(currentX, currentY);
                    if (currentCell) {
                        cout << "\n> You attempt to dig..." << endl;
                        currentCell->dig(*player);
                    }
                }
                continue;

            case 'q':
                // Quit game
                cout << "\n> Exiting game. Goodbye!" << endl;
                try
                {
                    logger->log("Player quitted game.");
                    logger->log(GameHelper::displayGameState(*player, currentX,currentY,currentDimension,false), "../final_report.txt"); // do not show controls
                }
                catch (ErrorArchivo& e)
                {
                    std::cerr << e.what() << endl;
                }
                gameRunning = false;
                continue;

            default:
                cout << "\n> Invalid input. Please use W, A, S, D to move, E to dig, or Q to quit." << endl;
                continue; // skip
        }

        // do stuff if player moved to a valid new cell
        try
        {
            logger->log("\nMoved "+moveDirection+" to ("+to_string(currentX)+"," + to_string(currentY) +").");
        }
        catch (const exception& e)
        {
            cerr << e.what() << endl;
        }

        // interact if new cell is valid
        newCell = currentDimension->getCell(currentX, currentY);
        if (newCell){
            if (newCell->getState() == CellState::UNEXPLORED) { newCell->setState(CellState::EXPLORED); }

            int interactResult = newCell->interact(*player);
            // -1 = nothing, 0 = not consumable, 1 = consumable, 2 = monster
            if (interactResult == 1) {
                try
                {
                    logger->log("New player status: " + player->toString());
                } catch (ErrorArchivo& e)
                {
                    cerr << e.what() << endl;
                }
                newCell->setContent(nullptr); // remove content if consumable
            } else if (interactResult == 2) {
                Monster* monster = nullptr;
                // TODO: should not interact again with monster after defeated
                // iniciate combat if possible
                if (monster = dynamic_cast<Monster*>(newCell->getContent()))
                {
                    int combatResult = GameHelper::combat(*player, *monster);
                    switch (combatResult)
                    {
                        case -1: // lost
                        try
                        {
                            logger->log("Player was defeated by " + monster->getType());
                        }catch (ErrorArchivo& e)
                        {
                            std::cerr << e.what() << endl;
                        }
                        break;
                        case 0:// ran away, spawn in another cell
                            currentX=rand() % currentDimension->getRows();
                            currentY=rand() % currentDimension->getCols();

                            try
                            {
                                logger->log("Player ran away from " + monster->getType() + " and ended up in (" + to_string(currentX) + "," + to_string(currentY) + ").");
                            }catch (ErrorArchivo& e)
                            {
                                std::cerr << e.what() << endl;
                            }

                            cout << "You escaped but ended up in a random cell! (whatever is in there will not harm you until you enter again)"<< endl << endl;
                        break;
                        case 1: // won
                            try
                            {
                                logger->log("Player defeated " + monster->getType());
                            }
                            catch (ErrorArchivo& e)
                            {
                                std::cerr << e.what() << endl;
                            }
                            // If monster was bossType special event occur
                            if (monster->isBossQ()) {
                                int nextIndex = gameMap->getCurrentDimensionIndex()+1;
                                if (nextIndex < gameMap->getDimensionCount()) {
                                    GameHelper::slowPrint("\n====== DIMENSION CLEARED ======");
                                    this_thread::sleep_for(chrono::milliseconds(400));
                                    GameHelper::slowPrint("The boss collapses to the ground...");
                                    this_thread::sleep_for(chrono::milliseconds(300));
                                    GameHelper::slowPrint("A portal opens before you... you step through.");
                                    this_thread::sleep_for(chrono::milliseconds(500));
                                    gameMap->releaseDimension(gameMap->getCurrentDimensionIndex());
                                    gameMap->changeDimension(nextIndex);
                                    currentDimension = gameMap->getCurrentDimension();
                                    currentX = 0; currentY = 0;
                                    try
                                    {
                                        logger->log("Player advanced to dimension " + to_string(nextIndex));
                                    }
                                    catch (ErrorArchivo& e)
                                    {
                                        std::cerr << e.what() << endl;
                                    }
                                }
                                else {
                                    GameHelper::slowPrint("\n====== YOU WIN ======");
                                    this_thread::sleep_for(chrono::milliseconds(500));
                                    GameHelper::slowPrint("The final boss crumbles into dust.");
                                    this_thread::sleep_for(chrono::milliseconds(300));
                                    GameHelper::slowPrint("Silence falls. The adventure is over.");
                                    this_thread::sleep_for(chrono::milliseconds(800));
                                    GameHelper::slowPrint("You made it.");
                                    try
                                    {
                                        logger->log("Player completed the game.");
                                        logger->log(GameHelper::displayGameState(*player, currentX,currentY,currentDimension,false), "../final_report.txt"); // do not show controls
                                    }
                                    catch (ErrorArchivo& e)
                                    {
                                        std::cerr << e.what() << endl;
                                    }
                                    gameRunning = false;
                                }
                            }
                        break;
                        default:
                            cerr << "\nInvalid input on switch for interactResult" << endl;
                    }
                }
                else
                {
                    cerr << "Error: interact returned 2 but content is not a Monster... somehow." << endl;
                }
            }

        }

        // Check if player is dead
        if ((*player).getHp() <= 0)
        {
            cout << "\n====== GAME OVER ======" << endl;
            cout << "You have been defeated!" << endl;

            // log final state
            try
            {
                logger->log("Player died.");
                logger->log("\nGame state:");
                logger->log(GameHelper::displayGameState(*player, currentX,currentY,currentDimension,false), "../final_report.txt"); // do not show controls
            }
            catch (ErrorArchivo& e)
            {
                std::cerr << e.what() << endl;
            }
            gameRunning = false;
        }

        cout << endl;
    }

    // Cleanup
    delete gameMap;

    return 0;
}
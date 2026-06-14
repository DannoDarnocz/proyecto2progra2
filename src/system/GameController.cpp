//
// Created by Daniel on 10/06/2026.
//

#include "../../headers/system/GameController.h"

int GameController::runGame() {
    srand(time(NULL));

    // Create logger
    Logger* logger = Logger::getInstance();
    GameHelper::safelog("\n --- New game started ---");

    // Load map from files
    Map* gameMap = nullptr;
    try
    {
        gameMap = GameHelper::loadMapFromFiles("../map_data.txt");
    }
    catch (const FileException& e)
    {
        cerr << "Error loading map: " << e.what() << endl;
        GameHelper::safelog(string("Map loading failed: ") + e.what());
        return 1;
    }

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

    cout << "====== BLOCK WORLD ======" << endl;
    cout << "Welcome, adventurer!" << endl << endl;


    bool gameRunning = true;
    int totalKills = 0;
    int totalEscapes = 0;
    int damageDealt = 0;
    int damageTaken = 0;
    int bossesKilled = 0;
    int debuffApplied = 0;
    int cellVisited = 0;
    int cellDug = 0;
    int bombExploded = 0;
    int medkitFound = 0;
    int powerUpCollected = 0;

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
                    cellVisited++;
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
                    cellVisited++;
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
                    cellVisited++;
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
                    cellVisited++;
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
                        currentCell->dig(*player,cellDug, medkitFound, bombExploded);
                    }
                }
                continue;

            case 'q':
                // Quit game
                cout << "\n> Exiting game. Goodbye!" << endl;
                try
                {
                    logger->log("Player quitted game.");
                    logger->exportReport(
                        GameHelper::displayGameState(*player, currentX,currentY,currentDimension,false),
                        "../final_report.txt",
                        false,
                        player->getLevel(),
                        gameMap->getCurrentDimensionIndex(),
                        totalKills,
                        totalEscapes,
                        damageDealt,
                        damageTaken,
                        bossesKilled,
                        debuffApplied,
                        cellVisited,
                        cellDug,
                        bombExploded,
                        medkitFound,
                        powerUpCollected); //Writes general information
                }
                catch (FileException& e)
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
        GameHelper::safelog("\nMoved "+moveDirection+" to ("+to_string(currentX)+"," + to_string(currentY) +").");

        // interact if new cell is valid
        newCell = currentDimension->getCell(currentX, currentY);
        if (newCell){
            if (newCell->getState() == CellState::UNEXPLORED) { newCell->setState(CellState::EXPLORED); }

            InteractResult interactResult = newCell->interact(*player, powerUpCollected);
            // -1 = nothing, 0 = not consumable, 1 = consumable, 2 = monster
            if (interactResult == InteractResult::CONSUMABLE) {
                GameHelper::safelog("New player status: " + player->toString());
                newCell->setContent(nullptr); // remove content if consumable
            } else if (interactResult == InteractResult::MONSTER) {
                Monster* monster = nullptr;
                // iniciate combat if possible
                if (monster = dynamic_cast<Monster*>(newCell->getContent()))
                {
                    int combatResult = GameHelper::combat(*player, *monster,damageDealt,damageTaken,debuffApplied);
                    switch (combatResult)
                    {
                        case -1: // lost
                            GameHelper::safelog("Player was defeated by " + monster->getType());
                            break;
                        case 0:// ran away, spawn in another cell
                            currentX=rand() % currentDimension->getRows();
                            currentY=rand() % currentDimension->getCols();
                            totalEscapes++;

                            GameHelper::safelog("Player ran away from " + monster->getType() + " and ended up in (" + to_string(currentX) + "," + to_string(currentY) + ").");

                            cout << "You escaped but ended up in a random cell! (whatever is in there will not harm you until you enter again)"<< endl << endl;
                            break;
                        case 1: // won
                            try
                            {
                                totalKills++;
                                logger->log("Player defeated " + monster->getType());
                                monster->setVisible(false); // invisible to player now, gets deleted after going to another dimension
                                player->clearPowerUps(); // clear powerups after combat win
                            }
                            catch (FileException& e)
                            {
                                std::cerr << e.what() << endl;
                            }
                            // If monster was bossType special event occur
                            if (monster->isBossQ()) {
                                bossesKilled++;
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
                                    GameHelper::safelog("Player advanced to dimension " + to_string(nextIndex));
                                }
                                else {
                                    GameHelper::slowPrint("\n====== YOU WIN ======");
                                    this_thread::sleep_for(chrono::milliseconds(500));
                                    GameHelper::slowPrint("The final boss crumbles into dust.");
                                    this_thread::sleep_for(chrono::milliseconds(300));
                                    GameHelper::slowPrint("Silence falls. The adventure is over.");
                                    this_thread::sleep_for(chrono::milliseconds(800));
                                    GameHelper::slowPrint("You made it.");
                                    try {
                                        logger->log("Player completed the game.");
                                        logger->exportReport(
                                            GameHelper::displayGameState(*player, currentX,currentY,currentDimension,false),
                                            "../final_report.txt",
                                            true,
                                            player->getLevel(),
                                            gameMap->getCurrentDimensionIndex(),
                                            totalKills,
                                            totalEscapes,
                                            damageDealt,
                                            damageTaken,
                                            bossesKilled,
                                            debuffApplied,
                                            cellVisited,
                                            cellDug,
                                            bombExploded,
                                            medkitFound,
                                            powerUpCollected); //Writes general information
                                    }
                                    catch (FileException& e)
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
            try {
                logger->log("Player died.");
                logger->log("\nGame state:");
                logger->exportReport(
                    GameHelper::displayGameState(*player, currentX,currentY,currentDimension,false),
                    "../final_report.txt",
                    false,
                    player->getLevel(),
                    gameMap->getCurrentDimensionIndex(),
                    totalKills,
                    totalEscapes,
                    damageDealt,
                    damageTaken,
                    bossesKilled,
                    debuffApplied,
                    cellVisited,
                    cellDug,
                    bombExploded,
                    medkitFound,
                    powerUpCollected); //Writes general information
            }catch (FileException& e)
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
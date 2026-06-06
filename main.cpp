#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cctype>
#include <limits>
#include <memory>
#include <thread>

#include "headers/content/Bomb.h"
#include "headers/world/Map.h"
#include "headers/world/Dimension.h"
#include "headers/world/Cell.h"
#include "headers/player/Player.h"
#include "headers/content/Monster.h"
#include "headers/strategies/HealthLockAttack.h"
#include "headers/strategies/NormalAttack.h"
#include "headers/strategies/WeakenerAttack.h"
#include "headers/system/Logger.h"

using namespace std;

// Forward declarations
Map* loadMapFromFiles(const string& dimensionsFile);
void displayCellInfo(Cell* cell, int x, int y);
void displayGameState(Player& player, int currentX, int currentY, Dimension* dimension);
char getPlayerInput();
void waitForEnter(bool = true);
int askInput(int, int, bool = true);
void clearBuffer();
string monsterNames(int dimension = 0);
unique_ptr<Content> createBoss(int dimension = 0);
unique_ptr<Content> createMonster(int dimension = 0);
void displayMap(Dimension* dimension, int playerX, int playerY);

int main()
{
    srand(time(NULL));

    // Load map from files
    Map* gameMap = loadMapFromFiles("../map_data.txt");

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

    cout << "====== DUNGEON ADVENTURE SIMULATION ======" << endl;
    cout << "Welcome, adventurer!" << endl << endl;


    bool gameRunning = true;

    // Main game loop
    while (gameRunning)
    {
        // Display current state
        displayMap(currentDimension, currentX, currentY);
        displayGameState(*player, currentX, currentY, currentDimension);

        // Get player input
        char input = static_cast<char>(tolower(getPlayerInput()));

        switch (input)
        {
            case 'w':
                // Move up (decrease X) {Rows are X}
                if (currentX > 0){
                    currentX--;
                    Cell* newCell = currentDimension->getCell(currentX, currentY);
                    if (newCell){
                        if (newCell->getState() == CellState::UNEXPLORED) { newCell->setState(CellState::EXPLORED); }
                        cout << "\n> You moved up." << endl;
                        newCell->interact(*player);
                    }
                }
                else{
                    cout << "\n> You cannot move further up. You are at the boundary." << endl;
                }
                break;

            case 'a':
                // Move left (decrease Y) {Columns are Y}
                if (currentY > 0) {
                    currentY--;
                    Cell* newCell = currentDimension->getCell(currentX, currentY);
                    if (newCell) {
                        if (newCell->getState() == CellState::UNEXPLORED) { newCell->setState(CellState::EXPLORED); }
                        cout << "\n> You moved left." << endl;
                        newCell->interact(*player);
                    }
                } else {
                    cout << "\n> You cannot move further left. You are at the boundary." << endl;
                }
                break;

            case 's':
                // Move down (increase X) {Rows are X}
                if (currentX < currentDimension->getRows() - 1){
                    currentX++;
                    Cell* newCell = currentDimension->getCell(currentX, currentY);
                    if (newCell){
                        if (newCell->getState() == CellState::UNEXPLORED) { newCell->setState(CellState::EXPLORED); }
                        cout << "\n> You moved down." << endl;
                        newCell->interact(*player);
                    }
                } else {
                    cout << "\n> You cannot move further down. You are at the boundary." << endl;
                }
                break;

            case 'd':
                // Move right (increase Y) {Columns are Y}
                if (currentY < currentDimension->getCols() - 1){
                    currentY++;
                    Cell* newCell = currentDimension->getCell(currentX, currentY);
                    if (newCell){
                        if (newCell->getState() == CellState::UNEXPLORED) { newCell->setState(CellState::EXPLORED); }
                        cout << "\n> You moved right." << endl;
                        newCell->interact(*player);
                    }
                } else{
                    cout << "\n> You cannot move further right. You are at the boundary." << endl;
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
                break;

            case 'q':
                // Quit game
                cout << "\n> Exiting game. Goodbye!" << endl;
                gameRunning = false;
                break;

            default:
                cout << "\n> Invalid input. Please use W, A, S, D to move, E to dig, or Q to quit." << endl;
                break;
        }

        // Check if player is dead
        if ((*player).getHp() <= 0)
        {
            cout << "\n====== GAME OVER ======" << endl;
            cout << "You have been defeated!" << endl;
            gameRunning = false;
        }

        cout << endl;
    }

    // Cleanup
    delete gameMap;

    return 0;
}

// Load map from input file (placeholder implementation)
Map* loadMapFromFiles(const string& dimensionsFile)
{
    Map* map = new Map();

    ifstream file(dimensionsFile);
    if (!file.is_open())
    {
        // Create a default small map if file doesn't exist
        cout << "Map file not found. Creating default map..." << endl;

        Dimension* dimension = new Dimension(5, 5);

        // Create cells for the dimension
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (i==0 && j==0) {
                    dimension->setCell(i,j,new Cell());
                    continue;
                }
                int roll = rand() % 3;  // 0 = empty, 1 = bomb, 2 = monster
                std::unique_ptr<Content> content = nullptr;
                if (roll == 1) { content = std::make_unique<Bomb>();}
                if (roll == 2) { content = createMonster(0);} //0 Default
                dimension->setCell(i, j, new Cell(std::move(content)));
            }
        }
        map->addDimension(dimension);
        cout << "Using default settings: 1D [5x5]\n";
        return map;
    }

    string token;
    int numDimensions;
    file >> token >> numDimensions; // Read "DIMENSIONS 3"

    for (int d = 0; d < numDimensions; d++) //The amount of dimensions of the game
    {
        int rows, cols;
        file >> token >> rows >> cols; // Read "DIM 8 10"

        Dimension* dimension = new Dimension(rows, cols);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                char cell;  //Each character represent something in the map
                file >> cell;  //Read Character { '.' = Empty, 'B' = Bomb, 'M' = Monster, 'J'|'K'|'F' = BOSS}

                if (i == 0 && j == 0)
                {
                    dimension->setCell(i, j, new Cell());
                    continue;
                }

                unique_ptr<Content> content = nullptr;

                if (cell == 'B')
                    content = make_unique<Bomb>();
                else if (cell == 'M')
                    content = createMonster(d);
                else if (cell == 'J' || cell == 'K' || cell == 'F')
                    content = createBoss(d);

                dimension->setCell(i, j, new Cell(move(content)));
            }
        }

        map->addDimension(dimension);
    }
    file.close();
    cout << "Using custom settings: 3D [8x10][10x12][5x12]\n";
    return map;
}

// Display information about the current cell
void displayCellInfo(Cell* cell, int x, int y)
{
    if (!cell)
    {
        cout << "Invalid cell!" << endl;
        return;
    }

    cout << "Cell (" << x << ", " << y << "): ";

    switch (cell->getState())
    {
        case CellState::UNEXPLORED:
            cout << "[UNEXPLORED]" << endl;
            break;
        case CellState::EXPLORED:
            cout << "[EXPLORED]" << endl;
            break;
        case CellState::DUG:
            cout << "[DUG]" << endl;
            break;
    }

    Content* content = cell->getContent();
    if (content && content->isVisible())
    {
        cout << content->toString() << endl;
    }
    else if (content && !content->isVisible())
    {
        Bomb* bomb = dynamic_cast<Bomb*>(content);
        Monster* monster = dynamic_cast<Monster*>(content);

        if (bomb && cell->getState() == CellState::DUG)
            cout << "Bomb fragments are scattered here." << endl;
        else if (monster && monster->getHp() <= 0)
            cout << "Remains of a " << monster->getType() << " lie here." << endl;
        else
            cout << "No visible content." << endl;
    }
    else
    {
        cout << "No visible content." << endl;
    }
}

// Display the current game state
void displayGameState(Player& player, int currentX, int currentY, Dimension* dimension)
{
    cout << "\n========================================" << endl;
    cout << "Player Status: HP=" << player.getHp() << " | Level=" << player.getLevel() << endl;
    cout << "Position: (" << currentX << ", " << currentY << ")" << endl;
    cout << "========================================" << endl;

    if (dimension)
    {
        Cell* currentCell = dimension->getCell(currentX, currentY);
        if (currentCell)
        {
            displayCellInfo(currentCell, currentX, currentY);
        }
    }

    cout << "\nControls: W=Up, A=Left, S=Down, D=Right, E=Dig, Q=Quit" << endl;
}

// Get player input
char getPlayerInput()
{
    cout << "Enter action: ";
    string input;
    getline(cin, input);

    if (!input.empty())
    {
        return input[0]; // return only the first character, doesnt require directly using cin and verifying input
    }
    return ' ';
}

// Wait for player to press ENTER
void waitForEnter(bool msg)
{
    if (msg)
    {
        cout << "Press ENTER to continue... ";
    }
    cin.ignore(100000, '\n');
}

// Ask for input in a specified range
int askInput(int min, int max, bool showText)
{
    int option;
    if (showText)
    {
        cout << "Enter the desired option: ";
    }

    // Repeat until valid input is received
    while (true)
    {
        cin >> option;
        // Verify that input is valid
        if (cin.fail())
        {
            clearBuffer();
            cout << "Invalid input. Please enter a number: ";
            continue;
        }
        if (option < min || option > max)
        {
            cout << "Option out of range. Enter a number between " << min << " and " << max << ": ";
            continue;
        }
        clearBuffer();
        return option;
    }
}

// Clear the input buffer
void clearBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void combat(Player& player, Monster& monster) {
    // Pre-combat: show stats and let player decide
    cout << "A " << monster.getType() << " appears!\n";
    cout << "Monster — HP: " << monster.getHp() << " | Damage: " << monster.getBaseDamage() << "\n";
    cout << "You    — HP: " << player.getHp() << " | Level: " << player.getLevel() << "\n\n";
    cout << "Do you want to (F)ight or (R)un? ";

    string choice;
    getline(cin, choice);
    if (choice == "r" || choice == "R") {
        // teleport to random cell in current dimension
        cout << "You run away in panic and end up somewhere else...\n";
        // TODO: randomize player position
        return;
    }

    cout << "--- COMBAT RULES ---\n"
    << "Combats are based on reflexes.\n"
    << "The system randomly decides if you have to ATTACK or DEFEND.\n"
    << "Press ENTER as quick as possible to ATTACK.\n"
    << "Type anything and then press ENTER to DEFEND.\n"
    << "Good luck!\n\n";
    waitForEnter();


    // Combat loop
    while (player.getHp() > 0 && monster.getHp() > 0) {

        // Random suspense delay before showing action
        int delay = 500 + rand() % 1500;
        this_thread::sleep_for(chrono::milliseconds(delay));

        // Randomly decide ATTACK or DEFEND
        bool shouldAttack = rand() % 2 == 0;

        if (shouldAttack) {
            cout << "ATTACK! Press ENTER as soon as possible!\n";
            // start measuring time until player presses ENTER
            auto start = chrono::steady_clock::now();
            string input;
            getline(cin, input);
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(
                chrono::steady_clock::now() - start).count();

            if (input.empty() && elapsed < 1000) {
                // Fast ENTER, player attacks
                int damage = (elapsed < 300) ? monster.getBaseDamage() * 2
                           : (elapsed < 600) ? monster.getBaseDamage() * 1.5
                           : monster.getBaseDamage();
                monster.takeDamage(damage);
                cout << "You attacked for " << damage << " damage!\n";
            } else {
                // Too slow or wrote something, monster attacks
                monster.attackPlayer(player);
                cout << "Too slow! The monster attacks you for " << monster.getBaseDamage() << " damage!\n";
            }

        } else {
            cout << "DEFEND! Take your time and type something, then press ENTER.\n";
            string input;
            getline(cin, input);

            if (!input.empty()) {
                // Wrote something, player defends
                if (player.getDebuff() == PlayerDebuff::HEALTH_LOCK) {
                    // Player cannot heal due to debuff from previous attack
                    cout << "Your health is locked and cannot be healed... But the effect went away!\n";
                    player.setDebuff(PlayerDebuff::NONE); // reset debuff
                    continue;
                }
                else
                {
                    // Player recovers HP
                    int heal = monster.getBaseDamage() / 2;
                    player.heal(heal);
                    cout << "You defended and recovered " << heal << " HP!\n";
                }
            } else {
                // Pressed ENTER with nothing, monster attacks
                monster.attackPlayer(player);
                cout << "You failed to defend! The monster attacks for " << monster.getBaseDamage() << " damage!\n";
            }
        }

        // Show result and wait for ENTER to continue
        cout << "Your HP: " << player.getHp() << " | Monster HP: " << monster.getHp() << "\n";
        cout << "Press ENTER to continue...";
        string pause;
        getline(cin, pause);
    }

    // Combat result
    if (monster.getHp() <= 0) {
        cout << "You defeated the " << monster.getType() << "!\n"
        << "Leveled up from " << player.getLevel() << " to " << player.getLevel() + 1 << ".\n";
        player.levelUp();
        // TODO: set cell content to nullptr
    } else {
        cout << "\nYou were defeated...\n";
        cout << "--- Adventure Log ---\n";
        Logger* logger = Logger::getInstance();
        logger->log("Player was defeated by a " + monster.getType() + ".");
    }
}

string monsterNames(int dimension) {
    if (dimension == 0) {
        int roll = rand() % 3;
        switch (roll) {
            case 0: return "Slime";
            case 1: return "Zombie";
            case 2: return "Goblin";
            default: return "Unknown";
        }
    } else {
        int roll = rand() % 3;
        switch (roll) {
            case 0: return "Skeleton";
            case 1: return "Possesed Armor";
            case 2: return "Demon";
            default: return "Unknown";
        }
    }
}

unique_ptr<Content> createMonster(int dimension)
{
    auto strategy = make_shared<NormalAttack>();
    int baseHp  = 100 + dimension * 50;
    int baseDmg = 5   + dimension * 10;
    int level   = 1   + dimension * 2;
    return make_unique<Monster>(
        rand() % 50 + baseHp,
        rand() % 15 + baseDmg,
        rand() % 3  + level,
        strategy,
        monsterNames(dimension));
}

unique_ptr<Content> createBoss(int dimension)
{
    auto strategy = make_shared<NormalAttack>();
    switch (dimension)
    {
        case 0: return make_unique<Monster>(200, 25, 3, strategy, "Stone Golem", true);
        case 1: return make_unique<Monster>(350, 40, 6, strategy, "Dark Knight", true);
        case 2: return make_unique<Monster>(600, 60, 10, strategy, "Demon Lord", true);
        default: return make_unique<Monster>(200, 25, 3, strategy, "Unknown Boss", true);
    }
}

void displayMap(Dimension* dimension, int playerX, int playerY)
{
    cout << "\n--- MAP ---" << endl;
    for (int i = 0; i < dimension->getRows(); i++){
        for (int j = 0; j < dimension->getCols(); j++){
            if (i == playerX && j == playerY) {
                cout << "P ";
                continue;
            }

            Cell* cell = dimension->getCell(i, j);
            if (cell == nullptr) { cout << "? "; continue; }

            CellState state = cell->getState();

            if (state == CellState::UNEXPLORED) {
                cout << ". ";
                continue;
            }

            // EXPLORED or DUG
            Content* content = cell->getContent();

            if (content && content->isVisible()) {
                Monster* m = dynamic_cast<Monster*>(content);
                if (m) {
                    cout << (m->isBossQ() ? "J " : "M ");
                }
                else {
                    cout << ". ";
                }
            }
            else if (content && !content->isVisible()) {
                Bomb* bomb = dynamic_cast<Bomb*>(content);

                if (bomb && state == CellState::DUG)
                    cout << "B ";
                else
                    cout << (state == CellState::DUG ? "X " : ". ");
            }
            else
            {
                // sin contenido o contenido invisible
                cout << (state == CellState::DUG ? "X " : ". ");
            }
        }
        cout << endl;
    }
    cout << "-----------" << endl;
}
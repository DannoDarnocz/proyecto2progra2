#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <limits>
#include "headers/world/Map.h"
#include "headers/world/Dimension.h"
#include "headers/world/Cell.h"
#include "headers/player/Player.h"
#include "headers/content/Monster.h"

using namespace std;

// Forward declarations
Map* loadMapFromFiles(const string& dimensionsFile);
void displayCellInfo(Cell* cell, int x, int y);
void displayGameState(Player& player, int currentX, int currentY, Dimension* dimension);
char getPlayerInput();
void waitForEnter(bool = true);
int askInput(int, int, bool = true);
void clearBuffer();

int main()
{
    // Load map from files
    Map* gameMap = loadMapFromFiles("map_data.txt");

    // Check if map was loaded successfully
    if (!gameMap || gameMap->getDimensionCount() == 0)
    {
        cerr << "Failed to load map from files. Exiting." << endl;
        return 1;
    }

    // Create player at starting position (0, 0) in first dimension
    Player player(100, 1);
    int currentX = 0;
    int currentY = 0;

    Dimension* currentDimension = gameMap->getCurrentDimension();

    // Validate starting position
    if (!currentDimension || !currentDimension->getCell(currentX, currentY))
    {
        cerr << "Invalid starting position. Exiting." << endl;
        return 1;
    }

    cout << "====== DUNGEON ADVENTURE SIMULATION ======" << endl;
    cout << "Welcome, adventurer!" << endl << endl;

    bool gameRunning = true;

    // Main game loop
    while (gameRunning)
    {
        // Display current state
        displayGameState(player, currentX, currentY, currentDimension);

        // Get player input
        char input = static_cast<char>(tolower(getPlayerInput()));

        switch (input)
        {
            case 'w':
                // Move up (decrease Y)
                if (currentY > 0)
                {
                    currentY--;
                    Cell* newCell = currentDimension->getCell(currentX, currentY);
                    if (newCell)
                    {
                        cout << "\n> You moved up." << endl;
                        newCell->interact(player);
                    }
                }
                else
                {
                    cout << "\n> You cannot move further up. You are at the boundary." << endl;
                }
                break;

            case 'a':
                // Move left (decrease X)
                if (currentX > 0)
                {
                    currentX--;
                    Cell* newCell = currentDimension->getCell(currentX, currentY);
                    if (newCell)
                    {
                        cout << "\n> You moved left." << endl;
                        newCell->interact(player);
                    }
                }
                else
                {
                    cout << "\n> You cannot move further left. You are at the boundary." << endl;
                }
                break;

            case 's':
                // Move down (increase Y)
                if (currentY < currentDimension->getCols() - 1)
                {
                    currentY++;
                    Cell* newCell = currentDimension->getCell(currentX, currentY);
                    if (newCell)
                    {
                        cout << "\n> You moved down." << endl;
                        newCell->interact(player);
                    }
                }
                else
                {
                    cout << "\n> You cannot move further down. You are at the boundary." << endl;
                }
                break;

            case 'd':
                // Move right (increase X)
                if (currentX < currentDimension->getRows() - 1)
                {
                    currentX++;
                    Cell* newCell = currentDimension->getCell(currentX, currentY);
                    if (newCell)
                    {
                        cout << "\n> You moved right." << endl;
                        newCell->interact(player);
                    }
                }
                else
                {
                    cout << "\n> You cannot move further right. You are at the boundary." << endl;
                }
                break;

            case 'e':
                // Dig current cell
                {
                    Cell* currentCell = currentDimension->getCell(currentX, currentY);
                    if (currentCell)
                    {
                        cout << "\n> You attempt to dig..." << endl;
                        currentCell->dig(player);
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
        if (player.getHp() <= 0)
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
                Cell* cell = new Cell();
                dimension->setCell(i, j, cell);
            }
        }

        map->addDimension(dimension);
        return map;
    }

    // TODO: Parse file and create dimensions and cells
    file.close();

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
        // TODO: polymorphic thing here
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
    cout << "Has Key: " << (player.hasKeyItem() ? "Yes" : "No") << endl;
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



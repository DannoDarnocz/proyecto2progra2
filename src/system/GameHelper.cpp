//
// Created by Daniel on 09/06/2026.
//

#include "../../headers/system/GameHelper.h"

// Load map from input file (placeholder implementation)
Map* GameHelper::loadMapFromFiles(const string& dimensionsFile)
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
                if (cell == 'H')
                    content = make_unique<Medkit>();
                else if (cell == 'M')
                    content = createMonster(d);
                else if (cell == '+')
                    content = make_unique<PowerUp>();
                else if (cell == 'J' || cell == 'K' || cell == 'F')
                    content = createBoss(d);

                dimension->setCell(i, j, new Cell(std::move(content)));
            }
        }

        map->addDimension(dimension);
    }
    file.close();
    cout << "Using custom settings: 3D [8x10][10x12][5x12]\n";
    return map;
}

// Display information about the current cell
void GameHelper::displayCellInfo(Cell* cell, int x, int y)
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
        Medkit* medkit = dynamic_cast<Medkit*>(content);

        if (medkit && (cell->getState() == CellState::DUG))
            cout << "An opened medkit lies here. Nothing useful left..." << endl;
        else if (bomb && cell->getState() == CellState::DUG)
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
string GameHelper::displayGameState(Player& player, int currentX, int currentY, Dimension* dimension, bool showControls) // does not show control when returning string
{
    stringstream s;

    s << "\n========================================" << endl;
    s << "Player Status: " << player.toString() << endl;
    s << "Position: (" << currentX << ", " << currentY << ")" << endl;
    s << "========================================" << endl;


    cout << s.str();

    if (dimension)
    {
        Cell* currentCell = dimension->getCell(currentX, currentY);
        if (currentCell && showControls)
        {
            displayCellInfo(currentCell, currentX, currentY);
        }
    }

    if (showControls)
    cout << "\nControls: W=Up, A=Left, S=Down, D=Right, E=Dig, Q=Quit" << endl;

    return s.str(); // return only player status and position
}

// Get player input
char GameHelper::getPlayerInput()
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
void GameHelper::waitForEnter(bool msg)
{
    if (msg)
    {
        cout << "Press ENTER to continue... ";
    }
    cin.ignore(100000, '\n');
}

// Ask for input in a specified range
int GameHelper::askInput(int min, int max, bool showText)
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
void GameHelper::clearBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//return 0 if escaped, return 1 if player won, return -1 if player lost
int GameHelper::combat(Player& player, Monster& monster, int& damageDealt, int& damageTaken, int& amountDebuffs) {
    // Pre-combat: show stats and let player decide
    cout << "A " << monster.getType() << " appears!\n";
    cout << "Monster: " << monster.toString() << "\n";
    cout << "You: " << player.toString()<<  "\n\n";
    cout << "Do you want to (F)ight or (R)un? ";

    string choice;
    getline(cin, choice);
    if (choice == "r" || choice == "R") {
        // teleport to random cell in current dimension
        cout << "You run away in panic and end up somewhere else...\n";
        return 0;
    }

    if (monster.isBossQ())
    {
        // give random powerup before battle
        cout << "You suddenly feel a rush of determination...\n";
        PowerUp newPower; // temp power just to interact and give random
        newPower.interact(player);
        waitForEnter();
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
        cout << "Hold your horses...\n";
        int delay = 100 + rand() % 3500;
        this_thread::sleep_for(chrono::milliseconds(delay));

        bool shouldAttack;
        // Randomly decide ATTACK or DEFEND
        shouldAttack = rand() % 2 == 0;


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
                if (player.getDebuff()==PlayerDebuff::WEAKNESS)
                {
                    // debuff, won't damage
                    cout << "You feel weak and cannot damage the enemy... But the effect went away!\n";
                    player.setDebuff(PlayerDebuff::NONE); // reset debuff
                }
                else
                {
                    // calc damage based on time elapsed
                    int damage = (elapsed < 300) ? player.calcDamage() * 1.5
                               : (elapsed < 600) ? player.calcDamage()
                               : monster.getBaseDamage();
                    monster.takeDamage(damage);
                    cout << "You attacked for " << damage << " damage!\n";
                    damageDealt = damageDealt + damage;
                }
            } else {
                // Too slow or wrote something, monster attacks
                monster.attackPlayer(player,amountDebuffs);
                std::string strategyName = monster.getAttackStrategyName();
                cout << "You were too slow..." <<endl;
                if (!strategyName.empty()) {
                    cout << "The monster uses " << strategyName << "! ";
                }
                cout << "The monster attacks you for " << monster.getDamage() << " damage!\n";
                damageTaken = damageTaken + monster.getDamage();
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
                monster.attackPlayer(player,amountDebuffs);
                std::string strategyName = monster.getAttackStrategyName();
                cout << "You didn't type anything..." <<endl;
                if (!strategyName.empty()) {
                    cout << "The monster uses " << strategyName << "! ";
                }
                cout << "It attacks you for " << monster.getDamage() << " damage!\n";
                damageTaken = damageTaken + monster.getDamage();
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
        return 1;
    } else {
        cout << "\nYou were defeated...\n";
        return -1;
    }
}

string GameHelper::monsterNames(int dimension) {
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

unique_ptr<Content> GameHelper::createMonster(int dimension)
{
    auto strategy = make_shared<NormalAttack>();
    int baseHp  = 30 + dimension * 50;
    int baseDmg = 5   + dimension * 10;
    int level   = 1   + dimension * 3;
    return make_unique<Monster>(
        rand() % 50 + baseHp,
        rand() % 15 + baseDmg,
        rand() % 3  + level,
        strategy,
        monsterNames(dimension));
}

unique_ptr<Content> GameHelper::createBoss(int dimension)
{
    auto strategy = make_shared<NormalAttack>();
    switch (dimension)
    {
        case 0: return make_unique<Monster>(200, 25, 3, strategy, "Stone Golem", true);
        case 1: return make_unique<Monster>(400, 40, 6, strategy, "Dark Knight", true);
        case 2: return make_unique<Monster>(600, 60, 10, strategy, "Demon Lord", true);
        default: return make_unique<Monster>(200, 25, 3, strategy, "Unknown Boss", true);
    }
}

void GameHelper::displayMap(Dimension* dimension, int playerX, int playerY)
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
                Medkit* k = dynamic_cast<Medkit*>(content);

                if (bomb && state == CellState::DUG)
                    cout << "B ";
                else if (k && state == CellState::DUG) {
                    cout << "H ";
                }
                else
                    cout << (state == CellState::DUG ? "X " : ". ");
            }
            else
            {
                // Without content
                cout << (state == CellState::DUG ? "X " : ". ");
            }
        }
        cout << endl;
    }
    cout << "-----------" << endl;
    cout << "[Bomb = B | Monster = M | Medkit = H | Player = P | Boss = J]" << endl;
}

void GameHelper::slowPrint(const string& text, int delayMs)
{
    for (char c : text)
    {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
    cout << endl;
}

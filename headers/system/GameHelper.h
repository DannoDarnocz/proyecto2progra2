//
// Created by Daniel on 09/06/2026.
//

#ifndef PROYECTO_II_LOGICHELPER_H
#define PROYECTO_II_LOGICHELPER_H
#include <memory>
#include <fstream>
#include <sstream>
#include <thread>
#include <iostream>

#include "../strategies/NormalAttack.h"
#include "../strategies/HealthLockAttack.h"
#include "../strategies/WeakenerAttack.h"
#include "../content/Monster.h"
#include "../content/Bomb.h"
#include "../content/Medkit.h"
#include "../world/Cell.h"
#include "../player/Player.h"
#include "../world/Map.h"
#include "Logger.h"

using namespace std;

namespace GameHelper
{
    // Forward declarations
    Map* loadMapFromFiles(const string& dimensionsFile);
    void displayCellInfo(Cell* cell, int x, int y);
    string displayGameState(Player& player, int currentX, int currentY, Dimension* dimension, bool showControls = true);
    char getPlayerInput();
    void waitForEnter(bool = true);
    int askInput(int, int, bool = true);
    void clearBuffer();
    string monsterNames(int dimension = 0);
    unique_ptr<Content> createBoss(int dimension = 0);
    unique_ptr<Content> createMonster(int dimension = 0);
    void displayMap(Dimension* dimension, int playerX, int playerY);
    int combat(Player& player, Monster& monster, int& damageDealt, int& damageTaken, int& amountDebuffs); // 0 if ran away, 1 if finished by either one dying
    void slowPrint(const string& text, int delayMs = 50);
    void safelog(const string& message);
};


#endif //PROYECTO_II_LOGICHELPER_H
//
// Created by Daniel on 10/06/2026.
//

#ifndef PROYECTO_II_GAMECONTROLLER_H
#define PROYECTO_II_GAMECONTROLLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cctype>
#include <limits>
#include <memory>
#include <thread>

#include "../../headers/system/GameHelper.h"
#include "../../headers/content/Bomb.h"
#include "../../headers/content/Medkit.h"
#include "../../headers/world/Map.h"
#include "../../headers/world/Dimension.h"
#include "../../headers/world/Cell.h"
#include "../../headers/player/Player.h"
#include "../../headers/content/Monster.h"
#include "../../headers/exceptions/FileException.h"
#include "../../headers/strategies/HealthLockAttack.h"
#include "../../headers/strategies/NormalAttack.h"
#include "../../headers/strategies/WeakenerAttack.h"
#include "../../headers/system/Logger.h"

using namespace std;

struct GameController
{
    static int runGame();
};

#endif //PROYECTO_II_GAMECONTROLLER_H
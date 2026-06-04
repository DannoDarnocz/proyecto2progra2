cmake_minimum_required(VERSION 4.1)
project(Proyecto_II)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto_II main.cpp
        # World Module
        headers/world/Dimension.h
        headers/world/Cell.h
        headers/world/Map.h
        src/world/Dimension.cpp
        src/world/Cell.cpp
        src/world/Map.cpp

        # Content Module
        headers/content/Content.h
        headers/content/Monster.h
        src/content/Content.cpp
        src/content/Monster.cpp

        # Player Module
        headers/player/Player.h
        src/player/Player.cpp

        # Powers Module
        headers/content/PowerUp.h
        headers/content/PowerUpDecorator.h
        src/powers/PowerUp.cpp
        src/powers/PowerUpDecorator.cpp

        # Strategies Module
        headers/strategies/AttackStrategy.h
        headers/strategies/NormalAttack.h
        headers/strategies/HealthLockAttack.h
        headers/strategies/WeakenerAttack.h
        src/strategies/AttackStrategy.cpp
        src/strategies/NormalAttack.cpp
        src/strategies/HealthLockAttack.cpp
        src/strategies/WeakenerAttack.cpp

        # System Module
        headers/system/EventObserver.h
        headers/system/Logger.h
        headers/system/MapObserver.h
        headers/system/LoggerObserver.h
        src/system/EventObserver.cpp
        src/system/Logger.cpp
        src/system/MapObserver.cpp
        src/system/LoggerObserver.cpp
        headers/content/Bomb.h
        src/content/Bomb.cpp
)

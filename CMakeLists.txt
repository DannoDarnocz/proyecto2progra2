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
        headers/content/Chest.h
        headers/content/Portal.h
        src/content/Content.cpp
        src/content/Monster.cpp
        src/content/Chest.cpp
        src/content/Portal.cpp

        # Player Module
        headers/player/Player.h
        src/player/Player.cpp

        # Combat Module
        headers/combat/Combat.h
        src/combat/Combat.cpp

        # Powers Module
        headers/powers/Power.h
        headers/powers/PowerDecorator.h
        src/powers/Power.cpp
        src/powers/PowerDecorator.cpp

        # Strategies Module
        headers/strategies/AttackStrategy.h
        headers/strategies/NormalAttack.h
        headers/strategies/PoisonAttack.h
        headers/strategies/StunAttack.h
        src/strategies/AttackStrategy.cpp
        src/strategies/NormalAttack.cpp
        src/strategies/PoisonAttack.cpp
        src/strategies/StunAttack.cpp

        # System Module
        headers/system/EventObserver.h
        headers/system/Logger.h
        headers/system/MapObserver.h
        headers/system/LoggerObserver.h
        src/system/EventObserver.cpp
        src/system/Logger.cpp
        src/system/MapObserver.cpp
        src/system/LoggerObserver.cpp)

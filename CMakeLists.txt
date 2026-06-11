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
        headers/system/Logger.h
        src/system/Logger.cpp
        headers/content/Bomb.h
        src/content/Bomb.cpp
        headers/content/Medkit.h
        src/content/Medkit.cpp
        headers/exceptions/FileException.h
        headers/exceptions/FileExceptionOut.h
        headers/exceptions/FileExceptionIn.h
        headers/exceptions/ErrorCast.h
        headers/exceptions/ErrorDecimal.h
        headers/exceptions/ErrorNegativo.h
        headers/exceptions/ErrorPuntero.h
        headers/exceptions/ErrorRango.h
        headers/exceptions/ErrorValor.h
        src/exceptions/FileException.cpp
        src/exceptions/FileExceptionOut.cpp
        src/exceptions/FileExceptionIn.cpp
        src/exceptions/ErrorCast.cpp
        src/exceptions/ErrorDecimal.cpp
        src/exceptions/ErrorNegativo.cpp
        src/exceptions/ErrorPuntero.cpp
        src/exceptions/ErrorRango.cpp
        src/exceptions/ErrorValor.cpp
        headers/system/GameHelper.h
        src/system/GameHelper.cpp
        headers/player/IStats.h
        headers/player/BaseStats.h
        src/player/BaseStats.cpp
        headers/player/StatsDecorator.h
        src/player/StatsDecorator.cpp
        headers/player/ExtraHealthStats.h
        src/player/ExtraHealthStats.cpp
        headers/player/ExtraDamageStats.h
        src/player/ExtraDamageStats.cpp
        src/content/PowerUp.cpp
        headers/system/GameController.h
        src/system/GameController.cpp
        headers/strategies/LeechAttack.h
        src/strategies/LeechAttack.cpp
)

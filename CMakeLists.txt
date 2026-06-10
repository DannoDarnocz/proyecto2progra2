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
        src/content/PowerUp.cpp
        src/content/PowerUpDecorator.cpp

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
        headers/exceptions/ErrorArchivo.h
        headers/exceptions/ErrorArchivoEscritura.h
        headers/exceptions/ErrorArchivoLectura.h
        headers/exceptions/ErrorCast.h
        headers/exceptions/ErrorDecimal.h
        headers/exceptions/ErrorNegativo.h
        headers/exceptions/ErrorPuntero.h
        headers/exceptions/ErrorRango.h
        headers/exceptions/ErrorValor.h
        src/exceptions/ErrorArchivo.cpp
        src/exceptions/ErrorArchivoEscritura.cpp
        src/exceptions/ErrorArchivoLectura.cpp
        src/exceptions/ErrorCast.cpp
        src/exceptions/ErrorDecimal.cpp
        src/exceptions/ErrorNegativo.cpp
        src/exceptions/ErrorPuntero.cpp
        src/exceptions/ErrorRango.cpp
        src/exceptions/ErrorValor.cpp
        headers/content/PowerUpHealth.h
        headers/content/PowerUpAttack.h
        headers/system/GameHelper.h
        src/system/GameHelper.cpp
)

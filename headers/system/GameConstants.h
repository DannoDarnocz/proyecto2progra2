//
// Created by axel on 14/6/2026.
//

#ifndef PROYECTO_II_GAMECONSTANTS_H
#define PROYECTO_II_GAMECONSTANTS_H

// Centralized gameplay balance constants.
namespace GameConstants
{
    // --- Bomb ---
    constexpr float BOMB_DAMAGE = 0.3f; // Bomb deals 30% of player's current HP

    // --- Monster attack strategies ---
    constexpr float WEAKENER_DAMAGE   = 0.8f; // Weakener attack deals 80% of base damage
    constexpr float HEALTH_LOCK_DAMAGE = 0.8f; // Health Lock attack deals 80% of base damage
    constexpr float LEECH_DAMAGE      = 0.5f; // Leech attack deals 50% of base damage

    // --- Player power-ups (Decorator pattern) ---
    constexpr float EXTRA_DAMAGE_MULTIPLIER = 1.2f; // +20% damage
    constexpr float EXTRA_HEALTH_MULTIPLIER = 1.3f; // +30% max health
    constexpr int   HEALTH_POWERUP_HEAL_AMOUNT = 30; // immediate heal when picking up health power-up

    // --- Base player stats (BaseStats) ---
    constexpr int BASE_PLAYER_HP        = 100; // HP at level 1
    constexpr int PLAYER_HP_PER_LEVEL   = 15;  // HP gained per level
    constexpr int BASE_PLAYER_DAMAGE    = 15;  // Damage at level 1
    constexpr int PLAYER_DAMAGE_PER_LEVEL = 10; // Damage gained per level

    // --- Monster damage scaling ---
    constexpr int MONSTER_DAMAGE_PER_LEVEL = 10; // extra true damage per monster level above 1
}

#endif //PROYECTO_II_GAMECONSTANTS_H
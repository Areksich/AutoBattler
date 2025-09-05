#pragma once
#include "Character/Character.h"
#include "Enemy/Enemy.h"
#include <memory>

using namespace std;

enum class GameState {
    CHARACTER_CREATION,
    BATTLE,
    LEVEL_UP,
    VICTORY,
    DEFEAT
};

class Game {
private:
    unique_ptr<Character> player;
    GameState currentState;
    int monstersDefeated;
    static const int MONSTERS_TO_WIN = 5;
    static const int MAX_LEVEL = 3;

public:
    Game();
    ~Game() = default;
    
    // Основной игровой цикл
    void run();
    
    // Управление состояниями
    void changeState(GameState newState) { currentState = newState; }
    GameState getCurrentState() const { return currentState; }

private:
    // Обработка состояний
    void handleCharacterCreation();
    void handleBattle();
    void handleLevelUp();
    void handleWeaponSelection(const Weapon& newWeapon);
    void handleVictory();
    void handleDefeat();
    
    // Игровая логика
    void createNewCharacter();
    Enemy getRandomEnemy() const;
    void processVictory(const Enemy& defeatedEnemy);
    void processDefeat();
    
    // Проверки состояния игры
    bool shouldLevelUp() const { return player && player->getTotalLevel() < MAX_LEVEL; }
    bool isGameWon() const { return monstersDefeated >= MONSTERS_TO_WIN; }
    bool wantsToPlayAgain() const;
};
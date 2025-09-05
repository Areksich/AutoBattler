#include "GameEntity.h"

GameEntity::GameEntity(const string& entityName, int hp, int str, int dex, int end)
        : name(entityName), health(hp), maxHealth(hp), strength(str), dexterity(dex), endurance(end) {}

        void GameEntity::takeDamage(int damage) {
        health = max(0, health - damage);
    }
    
    void GameEntity::heal(int amount) {
        health = min(maxHealth, health + amount);
    }
    
    void GameEntity::restoreHealth() {
        health = maxHealth;
    }
    
    bool GameEntity::isAlive() const {
        return health > 0;
    }
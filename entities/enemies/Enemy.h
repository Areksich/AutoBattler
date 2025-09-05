#pragma once
#include "core/GameEntity.h"
#include "core/Random.h"
#include <memory>
#include <string>

using namespace std;

// Базовый класс врага
class Enemy : public GameEntity {
protected:
    int weaponDamage;
    string rewardWeapon;
    int turnCounter;
    
public:
    Enemy(const string& enemyName, int hp, int weaponDmg, int str, int dex, int end, const string& reward);
    
    const string& getReward() const { return rewardWeapon; }
    void incrementTurn() { turnCounter++; }
    int getTurnCounter() const { return turnCounter; }
    
    // Боевые методы
    int calculateBaseDamage() const override;
    int applyAttackEffects(const GameEntity& target, int baseDamage, int turn) const override;
    int applyDefenseEffects(const GameEntity& attacker, int incomingDamage) const override;
    
    virtual bool hasSpecialAttack(int turn) const { return false; }
    virtual int getSpecialDamage() const { return 0; }
};

// Фабрика врагов
class EnemyFactory {
public:
    static unique_ptr<Enemy> createRandomEnemy();
};
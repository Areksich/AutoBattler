#pragma once
#include "Enemy.h"
#include <iostream>

using namespace std;

// Конкретные типы врагов
class Goblin : public Enemy {
public:
    Goblin();
};

class Skeleton : public Enemy {
public:
    Skeleton();
    int applyDefenseEffects(const GameEntity& attacker, int incomingDamage) const override;
};

class Slime : public Enemy {
public:
    Slime();
};

class Ghost : public Enemy {
public:
    Ghost();
    int applyAttackEffects(const GameEntity& target, int baseDamage, int turn) const override;
};

class Golem : public Enemy {
public:
    Golem();
    int applyDefenseEffects(const GameEntity& attacker, int incomingDamage) const override;
};

class Dragon : public Enemy {
public:
    Dragon();
    bool hasSpecialAttack(int turn) const override;
    int getSpecialDamage() const override;
};
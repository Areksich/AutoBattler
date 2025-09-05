#include "Enemy.h"
#include "EnemyTypes.h"

// Реализация Enemy
Enemy::Enemy(const string& enemyName, int hp, int weaponDmg, int str, int dex, int end, const string& reward)
    : GameEntity(enemyName, hp, str, dex, end), weaponDamage(weaponDmg), rewardWeapon(reward), turnCounter(0) {}

int Enemy::calculateBaseDamage() const {
    return weaponDamage + strength;
}

int Enemy::applyAttackEffects(const GameEntity& target, int baseDamage, int turn) const {
    return baseDamage;
}

int Enemy::applyDefenseEffects(const GameEntity& attacker, int incomingDamage) const {
    return incomingDamage;
}

// Реализация фабрики
unique_ptr<Enemy> EnemyFactory::createRandomEnemy() {
    int enemyType = Random::getInt(0, 5);
    
    switch (enemyType) {
        case 0: return make_unique<Goblin>();
        case 1: return make_unique<Skeleton>();
        case 2: return make_unique<Slime>();
        case 3: return make_unique<Ghost>();
        case 4: return make_unique<Golem>();
        case 5: return make_unique<Dragon>();
        default: return make_unique<Goblin>();
    }
}

// Реализация конкретных врагов
Goblin::Goblin() : Enemy("Гоблин", 5, 2, 1, 1, 1, "Кинжал") {}

Skeleton::Skeleton() : Enemy("Скелет", 10, 2, 2, 2, 1, "Дубина") {}

int Skeleton::applyDefenseEffects(const GameEntity& attacker, int incomingDamage) const {
    return incomingDamage;
}

Slime::Slime() : Enemy("Слайм", 8, 1, 3, 1, 2, "Копье") {}

Ghost::Ghost() : Enemy("Призрак", 6, 3, 1, 3, 1, "Меч") {}

int Ghost::applyAttackEffects(const GameEntity& target, int baseDamage, int turn) const {
    if (dexterity > target.getDexterity()) {
        cout << "Скрытая атака призрака! +1 урон" << endl;
        return baseDamage + 1;
    }
    return baseDamage;
}

Golem::Golem() : Enemy("Голем", 10, 1, 3, 1, 3, "Топор") {}

int Golem::applyDefenseEffects(const GameEntity& attacker, int incomingDamage) const {
    cout << "Каменная кожа голема! Урон снижен на " << endurance << endl;
    return max(0, incomingDamage - endurance);
}

Dragon::Dragon() : Enemy("Дракон", 20, 4, 3, 3, 3, "Легендарный Меч") {}

bool Dragon::hasSpecialAttack(int turn) const {
    return turn % 3 == 0;
}

int Dragon::getSpecialDamage() const {
    return weaponDamage + strength + 3;
}
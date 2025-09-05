#pragma once
#include "../Combat/Weapon.h"
#include <string>
#include <map>

using namespace std;

enum class EnemyType
{
    GOBLIN,
    SKELETON,
    SLIME,
    GHOST,
    GOLEM,
    DRAGON
};

// Структура для хранения неизменяемых данных о враге
struct EnemyData
{
    string name;
    int maxHealth;
    int weaponDamage;
    int strength;
    int dexterity;
    int endurance;
    string specialAbility;
    string reward;
};

class Enemy
{
private:
    // База данных врагов - статическая, создается один раз
    static const map<EnemyType, EnemyData> enemyDatabase;

    EnemyType type;
    const EnemyData *data;

    int currentHealth;
    int turnCounter;
    int poisonDamage;

public:
    Enemy(EnemyType enemyType);
    ~Enemy() = default;

    // Геттеры для неизменяемых данных (через указатель)
    const string &getName() const { return data->name; }
    int getMaxHealth() const { return data->maxHealth; }
    int getWeaponDamage() const { return data->weaponDamage; }
    int getStrength() const { return data->strength; }
    int getDexterity() const { return data->dexterity; }
    int getEndurance() const { return data->endurance; }
    const string &getSpecialAbility() const { return data->specialAbility; }
    const string &getReward() const { return data->reward; }
    EnemyType getType() const { return type; }

    // Геттеры для изменяемого состояния
    int getCurrentHealth() const { return currentHealth; }
    int getTurnCounter() const { return turnCounter; }
    int getPoisonDamage() const { return poisonDamage; }

    // Игровая логика
    void takeDamage(int damage);
    void incrementTurnCounter() { turnCounter++; }
    void addPoison(int damage) { poisonDamage += damage; }
    void applyPoisonDamage();
    void resetBattleState();

    // Проверки способностей (основаны на типе)
    bool hasSpecialAttack() const { return type == EnemyType::GHOST; }
    bool hasStoneskin() const { return type == EnemyType::GOLEM; }
    bool hasFireBreath() const { return type == EnemyType::DRAGON; }
    bool isImmuneToSlashing() const { return type == EnemyType::SLIME; }
    bool isVulnerableToCrushing() const { return type == EnemyType::SKELETON; }

    // Особые атаки
    int calculateSpecialAttackDamage(int turn) const;
    bool shouldUseSpecialAttack(int turn) const;

    // Защитные способности
    int applyDefensiveEffects(int incomingDamage, WeaponType weaponType) const;

    // Проверки состояния
    bool isAlive() const { return currentHealth > 0; }

    // Отображение
    void displayInfo() const;

    // Статический метод для получения данных о враге
    static const EnemyData &getEnemyData(EnemyType type)
    {
        return enemyDatabase.at(type);
    }
};
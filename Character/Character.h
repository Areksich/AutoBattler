#pragma once
#include "CharacterClass.h"
#include "../Combat/Weapon.h"
#include <vector>
#include <memory>

using namespace std;

class Character
{
private:
    int strength;
    int dexterity;
    int endurance;
    int currentHealth;
    int maxHealth;
    Weapon weapon;
    vector<unique_ptr<CharacterClassAbility>> abilities;
    int totalLevel;
    int rageCounter;

public:
    Character();
    ~Character() = default;

    // Инициализация
    void generateStats();
    void initialize(ClassType startClass);

    // Геттеры
    int getStrength() const { return strength; }
    int getDexterity() const { return dexterity; }
    int getEndurance() const { return endurance; }
    int getCurrentHealth() const { return currentHealth; }
    int getMaxHealth() const { return maxHealth; }
    const Weapon &getWeapon() const { return weapon; }
    int getTotalLevel() const { return totalLevel; }
    const vector<unique_ptr<CharacterClassAbility>> &getAbilities() const { return abilities; }

    // Сеттеры
    void setWeapon(const Weapon &newWeapon) { weapon = newWeapon; }

    // Игровая логика
    void takeDamage(int damage);
    void restoreHealth();
    void levelUp(ClassType newClass);

    // Бой
    void resetBattleState();
    int calculateAttackDamage() const;
    int modifyAttackDamageWithAbilities(int baseDamage, const class Enemy &target, int turn) const;
    int applyDefensiveEffects(int incomingDamage, const class Enemy &attacker) const;
    void onAttack(const Enemy &target, int turn);
    void onTurnStart();

    // Проверки
    bool hasClass(ClassType classType) const;
    int getClassLevel(ClassType classType) const;
    bool isAlive() const { return currentHealth > 0; }

    // Отображение
    void displayStats() const;
    void displayAbilities() const;

private:
    void applyStatBonuses(ClassType cls, int level);
    void addAbility(unique_ptr<CharacterClassAbility> ability);
};
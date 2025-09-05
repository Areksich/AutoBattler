#include "Enemy.h"
#include <iostream>
#include <algorithm>

// Инициализация статической базы данных врагов
const map<EnemyType, EnemyData> Enemy::enemyDatabase = {
    {EnemyType::GOBLIN,
     {"Гоблин", 5, 2, 1, 1, 1, "", "Кинжал"}},

    {EnemyType::SKELETON,
     {"Скелет", 10, 2, 2, 2, 1, "Уязвим к дробящему", "Дубина"}},

    {EnemyType::SLIME,
     {"Слайм", 8, 1, 3, 1, 2, "Иммунитет к рубящему", "Копье"}},

    {EnemyType::GHOST,
     {"Призрак", 6, 3, 1, 3, 1, "Скрытая атака", "Меч"}},

    {EnemyType::GOLEM,
     {"Голем", 10, 1, 3, 1, 3, "Каменная кожа", "Топор"}},

    {EnemyType::DRAGON,
     {"Дракон", 20, 4, 3, 3, 3, "Огненное дыхание", "Легендарный Меч"}}};

Enemy::Enemy(EnemyType enemyType)
    : type(enemyType),
      data(&enemyDatabase.at(enemyType)), // Получаем указатель на данные
      currentHealth(data->maxHealth),     // Инициализируем текущее здоровье
      turnCounter(0),
      poisonDamage(0)
{
}

void Enemy::takeDamage(int damage)
{
    currentHealth = max(0, currentHealth - damage);
}

void Enemy::applyPoisonDamage()
{
    if (poisonDamage > 0)
    {
        currentHealth = max(0, currentHealth - poisonDamage);
        cout << "Яд наносит " << poisonDamage << " урона! ";
        cout << "Здоровье " << getName() << ": " << currentHealth << "/" << getMaxHealth() << " HP" << endl;

        poisonDamage++;
    }
}

void Enemy::resetBattleState()
{
    currentHealth = data->maxHealth; // Восстанавливаем здоровье до максимума
    turnCounter = 0;
    poisonDamage = 0;
}

int Enemy::calculateSpecialAttackDamage(int turn) const
{
    int baseDamage = getWeaponDamage() + getStrength();

    // Особая атака дракона каждый 3-й ход
    if (hasFireBreath() && turnCounter > 0 && turnCounter % 3 == 0)
    {
        cout << "Дракон дышит огнём!" << endl;
        return baseDamage + 3;
    }

    return baseDamage;
}

bool Enemy::shouldUseSpecialAttack(int turn) const
{
    if (hasFireBreath())
    {
        return turnCounter > 0 && turnCounter % 3 == 0;
    }
    return false;
}

int Enemy::applyDefensiveEffects(int incomingDamage, WeaponType weaponType) const
{
    int damage = incomingDamage;

    // Каменная кожа голема
    if (hasStoneskin())
    {
        int reduction = getEndurance();
        damage = max(0, damage - reduction);
        cout << "Каменная кожа голема поглощает " << reduction << " урона!" << endl;
    }

    return damage;
}

void Enemy::displayInfo() const
{
    cout << "\n=== " << getName() << " ===" << endl;
    cout << "HP: " << currentHealth << "/" << getMaxHealth();

    if (!getSpecialAbility().empty())
    {
        cout << " | " << getSpecialAbility();
    }

    cout << endl;
    cout << "Сила: " << getStrength()
         << " | Ловкость: " << getDexterity()
         << " | Выносливость: " << getEndurance() << endl;
}
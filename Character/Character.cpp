#include "Character.h"
#include "CharacterClass.h"
#include "../Utils/Random.h"
#include "../UI/Display.h"
#include <iostream>
#include <algorithm>

Character::Character() : totalLevel(0), rageCounter(0),
                         weapon(WeaponFactory::getWeapon(WeaponName::DAGGER)) {}

void Character::generateStats()
{
    strength = RandomGenerator::getInt(1, 3);
    dexterity = RandomGenerator::getInt(1, 3);
    endurance = RandomGenerator::getInt(1, 3);
    totalLevel = 0;

    cout << "\n=== ВЫПАВШИЕ ХАРАКТЕРИСТИКИ ===" << endl;
    cout << "Сила: " << strength << endl;
    cout << "Ловкость: " << dexterity << endl;
    cout << "Выносливость: " << endurance << endl;
}

void Character::initialize(ClassType startClass)
{
    weapon = AbilityFactory::getStartingWeapon(startClass);
    totalLevel = 1;

    maxHealth = AbilityFactory::getHealthPerLevel(startClass) + endurance;
    currentHealth = maxHealth;

    // Добавляем способность 1-го уровня
    addAbility(AbilityFactory::createAbility(startClass, 1, this));

    cout << "\n=== ПЕРСОНАЖ СОЗДАН ===" << endl;
    displayStats();
}

void Character::takeDamage(int damage)
{
    currentHealth = max(0, currentHealth - damage);
}

void Character::restoreHealth()
{
    currentHealth = maxHealth;
}

void Character::levelUp(ClassType newClass)
{
    if (totalLevel >= 3)
        return;

    int currentClassLevel = getClassLevel(newClass);
    int newLevel = currentClassLevel + 1;

    totalLevel++;

    addAbility(AbilityFactory::createAbility(newClass, newLevel, this));

    applyStatBonuses(newClass, newLevel);

    maxHealth += AbilityFactory::getHealthPerLevel(newClass) + endurance;
    currentHealth = maxHealth;

    cout << "\n=== УРОВЕНЬ ПОВЫШЕН! ===" << endl;
    displayStats();
}

void Character::resetBattleState()
{
    // Сбрасываем счетчики способностей
    for (const auto &ability : abilities)
    {
        if (ability->getName() == "Ярость")
        {
            if (auto *rage = dynamic_cast<const Rage *>(ability.get()))
            {
                rage->resetCounter();
            }
        }
    }
}

int Character::calculateAttackDamage() const
{
    return weapon.getDamage() + strength;
}

int Character::modifyAttackDamageWithAbilities(int baseDamage, const Enemy &target, int turn) const
{
    int finalDamage = baseDamage;

    for (const auto &ability : abilities)
    {
        finalDamage = ability->modifyAttackDamage(finalDamage, target, turn);
    }

    return finalDamage;
}

int Character::applyDefensiveEffects(int incomingDamage, const Enemy &attacker) const
{
    int finalDamage = incomingDamage;

    for (const auto &ability : abilities)
    {
        finalDamage = ability->modifyDefense(finalDamage, attacker);
    }

    return max(0, finalDamage);
}

void Character::onAttack(const Enemy &target, int turn)
{
    for (const auto &ability : abilities)
    {
        ability->onAttack(target);
    }
}

void Character::onTurnStart()
{
    for (const auto &ability : abilities)
    {
        ability->onTurnStart();
    }
}

bool Character::hasClass(ClassType classType) const
{
    for (const auto &ability : abilities)
    {
        if (ability->getClassType() == classType)
        {
            return true;
        }
    }
    return false;
}

int Character::getClassLevel(ClassType classType) const
{
    int maxLevel = 0;
    for (const auto &ability : abilities)
    {
        if (ability->getClassType() == classType)
        {
            maxLevel = max(maxLevel, ability->getLevel());
        }
    }
    return maxLevel;
}

void Character::displayStats() const
{
    Display::showCharacterStats(*this);
}

void Character::displayAbilities() const
{
    if (abilities.empty())
    {
        cout << "Нет активных способностей" << endl;
        return;
    }

    for (const auto &ability : abilities)
    {
        cout << "- " << ability->getName() << ": " << ability->getDescription() << endl;
    }
}

void Character::applyStatBonuses(ClassType cls, int level)
{
    switch (cls)
    {
    case ClassType::ROGUE:
        if (level == 2)
        {
            dexterity++;
            cout << "Бонус разбойника: +1 к ловкости!" << endl;
        }
        break;
    case ClassType::WARRIOR:
        if (level == 3)
        {
            strength++;
            cout << "Бонус воина: +1 к силе!" << endl;
        }
        break;
    case ClassType::BARBARIAN:
        if (level == 3)
        {
            endurance++;
            cout << "Бонус варвара: +1 к выносливости!" << endl;
        }
        break;
    }
}

void Character::addAbility(unique_ptr<CharacterClassAbility> ability)
{
    abilities.push_back(move(ability));
}
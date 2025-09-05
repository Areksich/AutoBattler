#include "CharacterClass.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Weapon.h"
#include "Character.h"
#include <iostream>

// SneakAttack
int SneakAttack::modifyAttackDamage(int baseDamage, const Enemy &target, int turn) const
{
    if (owner && owner->getDexterity() > target.getDexterity())
    {
        return baseDamage + 1;
    }
    return baseDamage;
}

// Poison
void Poison::onAttack(const Enemy &target) const
{
    Enemy &mutableTarget = const_cast<Enemy &>(target);

    // Проверяем, наложен ли уже яд
    if (mutableTarget.getPoisonDamage() == 0)
    {
        // Накладываем яд впервые
        mutableTarget.addPoison(1);
        cout << "Противник отравлен! В следующем ходу получит урон от яда." << endl;
    }
}

// ActionSurge
int ActionSurge::modifyAttackDamage(int baseDamage, const Enemy &target, int turn) const
{
    if (turn == 1)
    {
        // Получаем урон от оружия и удваиваем его
        if (owner)
        {
            int weaponDamage = owner->getWeapon().getDamage();
            return baseDamage + weaponDamage; // Удваиваем урон оружия
        }
    }
    return baseDamage;
}

// Shield
int Shield::modifyDefense(int incomingDamage, const Enemy &attacker) const
{
    if (owner && owner->getStrength() > attacker.getStrength())
    {
        return max(0, incomingDamage - 3);
    }
    return incomingDamage;
}

// Rage
int Rage::modifyAttackDamage(int baseDamage, const Enemy &target, int turn) const
{
    if (rageCounter <= 3)
    {
        return baseDamage + 2;
    }
    else
    {
        return max(0, baseDamage - 1);
    }
}

void Rage::onTurnStart() const
{
    rageCounter++;
}

// Stoneskin
int Stoneskin::modifyDefense(int incomingDamage, const Enemy &attacker) const
{
    if (owner)
    {
        return max(0, incomingDamage - owner->getEndurance());
    }
    return max(0, incomingDamage - 2); // Fallback
}

// AbilityFactory
unique_ptr<CharacterClassAbility> AbilityFactory::createAbility(ClassType classType, int level, Character *owner)
{
    switch (classType)
    {
    case ClassType::ROGUE:
        switch (level)
        {
        case 1:
            return make_unique<SneakAttack>(owner);
        case 2:
            return make_unique<RogueDexterityBonus>(owner);
        case 3:
            return make_unique<Poison>(owner);
        }
        break;
    case ClassType::WARRIOR:
        switch (level)
        {
        case 1:
            return make_unique<ActionSurge>(owner);
        case 2:
            return make_unique<Shield>(owner);
        case 3:
            return make_unique<WarriorStrengthBonus>(owner);
        }
        break;
    case ClassType::BARBARIAN:
        switch (level)
        {
        case 1:
            return make_unique<Rage>(owner);
        case 2:
            return make_unique<Stoneskin>(owner);
        case 3:
            return make_unique<BarbarianEnduranceBonus>(owner);
        }
        break;
    }
    return nullptr;
}

string AbilityFactory::getClassName(ClassType classType)
{
    switch (classType)
    {
    case ClassType::ROGUE:
        return "Разбойник";
    case ClassType::WARRIOR:
        return "Воин";
    case ClassType::BARBARIAN:
        return "Варвар";
    }
    return "";
}

int AbilityFactory::getHealthPerLevel(ClassType classType)
{
    switch (classType)
    {
    case ClassType::ROGUE:
        return 4;
    case ClassType::WARRIOR:
        return 5;
    case ClassType::BARBARIAN:
        return 6;
    }
    return 0;
}

Weapon AbilityFactory::getStartingWeapon(ClassType classType)
{
    switch (classType)
    {
    case ClassType::ROGUE:
        return WeaponFactory::getWeapon(WeaponName::DAGGER);
    case ClassType::WARRIOR:
        return WeaponFactory::getWeapon(WeaponName::SWORD);
    case ClassType::BARBARIAN:
        return WeaponFactory::getWeapon(WeaponName::CLUB);
    }
    return WeaponFactory::getWeapon(WeaponName::DAGGER);
}
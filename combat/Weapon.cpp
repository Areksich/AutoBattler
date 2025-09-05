#include "Weapon.h"
#include <iostream>

Weapon::Weapon(const string &weaponName, int weaponDamage, WeaponType weaponType)
    : name(weaponName), damage(weaponDamage), type(weaponType) {}

void Weapon::displayInfo() const
{
    cout << name << " (Урон: " << damage << ", Тип: " << WeaponFactory::getWeaponTypeName(type) << ")";
}

Weapon WeaponFactory::getWeapon(WeaponName weaponName)
{
    switch (weaponName)
    {
    case WeaponName::SWORD:
        return Weapon("Меч", 3, WeaponType::SLASHING);
    case WeaponName::CLUB:
        return Weapon("Дубина", 3, WeaponType::CRUSHING);
    case WeaponName::DAGGER:
        return Weapon("Кинжал", 2, WeaponType::PIERCING);
    case WeaponName::AXE:
        return Weapon("Топор", 4, WeaponType::SLASHING);
    case WeaponName::SPEAR:
        return Weapon("Копье", 3, WeaponType::PIERCING);
    case WeaponName::LEGENDARY_SWORD:
        return Weapon("Легендарный Меч", 10, WeaponType::SLASHING);
    default:
        return Weapon("Кинжал", 2, WeaponType::PIERCING);
    }
}

Weapon WeaponFactory::getWeaponByName(const string &name)
{
    if (name == "Меч")
        return getWeapon(WeaponName::SWORD);
    if (name == "Дубина")
        return getWeapon(WeaponName::CLUB);
    if (name == "Кинжал")
        return getWeapon(WeaponName::DAGGER);
    if (name == "Топор")
        return getWeapon(WeaponName::AXE);
    if (name == "Копье")
        return getWeapon(WeaponName::SPEAR);
    if (name == "Легендарный Меч")
        return getWeapon(WeaponName::LEGENDARY_SWORD);

    return getWeapon(WeaponName::DAGGER); // По умолчанию
}

string WeaponFactory::getWeaponTypeName(WeaponType type)
{
    switch (type)
    {
    case WeaponType::SLASHING:
        return "Рубящее";
    case WeaponType::CRUSHING:
        return "Дробящее";
    case WeaponType::PIERCING:
        return "Колющее";
    default:
        return "Неизвестный";
    }
}
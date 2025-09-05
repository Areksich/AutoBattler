#include "Weapon.h"
#include <map>

Weapon::Weapon(const std::string& weaponName, int dmg, WeaponType weaponType)
    : name(weaponName), damage(dmg), type(weaponType) {}

const std::string& Weapon::getName() const { return name; }
int Weapon::getDamage() const { return damage; }
WeaponType Weapon::getType() const { return type; }

std::map<std::string, Weapon> WeaponFactory::weaponTemplates;

void WeaponFactory::initializeWeapons() {
    weaponTemplates = {
        {"Меч", Weapon("Меч", 3, WeaponType::SLASHING)},
        {"Дубина", Weapon("Дубина", 3, WeaponType::CRUSHING)},
        {"Кинжал", Weapon("Кинжал", 2, WeaponType::PIERCING)},
        {"Топор", Weapon("Топор", 4, WeaponType::SLASHING)},
        {"Копье", Weapon("Копье", 3, WeaponType::PIERCING)},
        {"Легендарный Меч", Weapon("Легендарный Меч", 10, WeaponType::SLASHING)}
    };
}

Weapon WeaponFactory::createWeapon(const std::string& weaponName) {
    auto it = weaponTemplates.find(weaponName);
    return (it != weaponTemplates.end()) ? it->second : Weapon();
}

bool WeaponFactory::weaponExists(const std::string& weaponName) {
    return weaponTemplates.find(weaponName) != weaponTemplates.end();
}
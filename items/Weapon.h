#pragma once
#include <string>
#include <map>

enum class WeaponType {
    SLASHING,  // Рубящий
    CRUSHING,  // Дробящий
    PIERCING   // Колющий
};

class Weapon {
private:
    std::string name;
    int damage;
    WeaponType type;
    
public:
    Weapon(const std::string& weaponName = "Кулаки", int dmg = 1, 
           WeaponType weaponType = WeaponType::CRUSHING);
    
    const std::string& getName() const;
    int getDamage() const;
    WeaponType getType() const;
};

class WeaponFactory {
private:
    static std::map<std::string, Weapon> weaponTemplates;
    
public:
    static void initializeWeapons();
    static Weapon createWeapon(const std::string& weaponName);
    static bool weaponExists(const std::string& weaponName);
};
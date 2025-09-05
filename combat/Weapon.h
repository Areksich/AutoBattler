#pragma once
#include <string>

using namespace std;

enum class WeaponType
{
    SLASHING,
    CRUSHING,
    PIERCING
};

enum class WeaponName
{
    SWORD,
    CLUB,
    DAGGER,
    AXE,
    SPEAR,
    LEGENDARY_SWORD
};

class Weapon
{
private:
    string name;
    int damage;
    WeaponType type;

public:
    Weapon(const string &weaponName, int weaponDamage, WeaponType weaponType);

    const string &getName() const { return name; }
    int getDamage() const { return damage; }
    WeaponType getType() const { return type; }

    void displayInfo() const;
};

class WeaponFactory
{
public:
    static Weapon getWeapon(WeaponName weaponName);
    static Weapon getWeaponByName(const string &name);
    static string getWeaponTypeName(WeaponType type);
};
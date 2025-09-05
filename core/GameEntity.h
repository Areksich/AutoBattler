#pragma once
#include <string>

using namespace std;

class GameEntity {
public:
    GameEntity(const string& entityName, int hp, int str, int dex, int end);
    virtual ~GameEntity() = default;
    
    const string& getName() const { return name; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    int getStrength() const { return strength; }
    int getDexterity() const { return dexterity; }
    int getEndurance() const { return endurance; }

    void takeDamage(int damage); 
    void heal(int amount);
    void restoreHealth();    
    bool isAlive() const;
    
    virtual int calculateBaseDamage() const = 0;
    virtual int applyAttackEffects(const GameEntity& target, int baseDamage, int turn) const = 0;
    virtual int applyDefenseEffects(const GameEntity& attacker, int incomingDamage) const = 0;

protected:
    string name;
    int health, maxHealth;
    int strength, dexterity, endurance;
};
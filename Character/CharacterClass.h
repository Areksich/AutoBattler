#pragma once
#include <string>
#include <memory>

using namespace std;

enum class ClassType
{
    ROGUE,
    WARRIOR,
    BARBARIAN
};

// Абстрактный базовый класс для способностей
class CharacterClassAbility
{
protected:
    class Character *owner;
    ClassType classType;
    int level;

public:
    CharacterClassAbility(class Character *character, ClassType type, int lvl)
        : owner(character), classType(type), level(lvl) {}

    virtual ~CharacterClassAbility() = default;

    // Основные геттеры
    virtual string getName() const = 0;
    virtual string getDescription() const = 0;
    ClassType getClassType() const { return classType; }
    int getLevel() const { return level; }

    // Эффекты способностей
    virtual int modifyAttackDamage(int baseDamage, const class Enemy &target, int turn) const { return baseDamage; }
    virtual int modifyDefense(int incomingDamage, const class Enemy &attacker) const { return incomingDamage; }
    virtual void onAttack(const class Enemy &target) const {}
    virtual void onTurnStart() const {}
};

// Cпособности разбойника
class SneakAttack : public CharacterClassAbility
{
public:
    explicit SneakAttack(class Character *character = nullptr)
        : CharacterClassAbility(character, ClassType::ROGUE, 1) {}

    string getName() const override { return "Скрытая атака"; }
    string getDescription() const override { return "+1 к урону, если ловкость > ловкости врага"; }
    int modifyAttackDamage(int baseDamage, const class Enemy &target, int turn) const override;
};

class RogueDexterityBonus : public CharacterClassAbility
{
public:
    explicit RogueDexterityBonus(class Character *character)
        : CharacterClassAbility(character, ClassType::ROGUE, 2) {}

    string getName() const override { return "+1 Ловкость"; }
    string getDescription() const override { return "Постоянное увеличение ловкости"; }
};

class Poison : public CharacterClassAbility
{
public:
    explicit Poison(class Character *character = nullptr)
        : CharacterClassAbility(character, ClassType::ROGUE, 3) {}

    string getName() const override { return "Яд"; }
    string getDescription() const override { return "+1 урон от яда каждый ход"; }
    void onAttack(const class Enemy &target) const override;
};

// Cпособности воина
class ActionSurge : public CharacterClassAbility
{
public:
    explicit ActionSurge(class Character *character = nullptr)
        : CharacterClassAbility(character, ClassType::WARRIOR, 1) {}

    string getName() const override { return "Порыв к действию"; }
    string getDescription() const override { return "Двойной урон оружием в первом ходу"; }
    int modifyAttackDamage(int baseDamage, const class Enemy &target, int turn) const override;
};

class Shield : public CharacterClassAbility
{
public:
    explicit Shield(class Character *character = nullptr)
        : CharacterClassAbility(character, ClassType::WARRIOR, 2) {}

    string getName() const override { return "Щит"; }
    string getDescription() const override { return "-3 урона, если сила > силы врага"; }
    int modifyDefense(int incomingDamage, const class Enemy &attacker) const override;
};

class WarriorStrengthBonus : public CharacterClassAbility
{
public:
    explicit WarriorStrengthBonus(class Character *character)
        : CharacterClassAbility(character, ClassType::WARRIOR, 3) {}

    string getName() const override { return "+1 Сила"; }
    string getDescription() const override { return "Постоянное увеличение силы"; }
};

// Cпособности варвара
class Rage : public CharacterClassAbility
{
private:
    mutable int rageCounter = 0;

public:
    explicit Rage(class Character *character = nullptr)
        : CharacterClassAbility(character, ClassType::BARBARIAN, 1) {}

    string getName() const override { return "Ярость"; }
    string getDescription() const override { return "+2 урон первые 3 хода, затем -1"; }
    int modifyAttackDamage(int baseDamage, const class Enemy &target, int turn) const override;
    void onTurnStart() const override;
    void resetCounter() const { rageCounter = 0; }
};

class Stoneskin : public CharacterClassAbility
{
public:
    explicit Stoneskin(class Character *character = nullptr)
        : CharacterClassAbility(character, ClassType::BARBARIAN, 2) {}

    string getName() const override { return "Каменная кожа"; }
    string getDescription() const override { return "Урон снижается на значение выносливости"; }
    int modifyDefense(int incomingDamage, const class Enemy &attacker) const override;
};

class BarbarianEnduranceBonus : public CharacterClassAbility
{
public:
    explicit BarbarianEnduranceBonus(class Character *character)
        : CharacterClassAbility(character, ClassType::BARBARIAN, 3) {}

    string getName() const override { return "+1 Выносливость"; }
    string getDescription() const override { return "Постоянное увеличение выносливости"; }
};

// Фабрика для создания способностей
class AbilityFactory
{
public:
    static unique_ptr<CharacterClassAbility> createAbility(ClassType classType, int level, class Character *owner = nullptr);
    static string getClassName(ClassType classType);
    static int getHealthPerLevel(ClassType classType);
    static class Weapon getStartingWeapon(ClassType classType);
};
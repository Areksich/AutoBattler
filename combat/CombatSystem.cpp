#include "CombatSystem.h"
#include "../Utils/Random.h"
#include "../Utils/InputHelper.h"
#include "../UI/Display.h"
#include <iostream>
#include <algorithm>

bool CombatSystem::executeBattle(Character &player, Enemy &enemy)
{
    cout << "\nБой начинается!" << endl;

    player.resetBattleState();
    enemy.resetBattleState();

    bool playerTurn = playerGoesFirst(player, enemy);

    int turn = 1;
    while (player.isAlive() && enemy.isAlive())
    {
        displayTurnInfo(player, enemy, turn);

        // Обновляем способности в начале хода
        player.onTurnStart();

        // Применяем урон от яда в начале хода
        enemy.applyPoisonDamage();
        if (!enemy.isAlive())
            break;

        if (playerTurn)
        {
            if (performPlayerAttack(player, enemy, turn) == AttackResult::HIT)
            {
                if (!enemy.isAlive())
                    break;
            }

            if (enemy.isAlive())
            {
                if (performEnemyAttack(enemy, player, turn) == AttackResult::HIT)
                {
                    if (!player.isAlive())
                        break;
                }
            }
        }
        else
        {
            if (performEnemyAttack(enemy, player, turn) == AttackResult::HIT)
            {
                if (!player.isAlive())
                    break;
            }

            if (player.isAlive())
            {
                if (performPlayerAttack(player, enemy, turn) == AttackResult::HIT)
                {
                    if (!enemy.isAlive())
                        break;
                }
            }
        }

        turn++;
    }

    return player.isAlive();
}

AttackResult CombatSystem::performPlayerAttack(Character &attacker, Enemy &target, int turn)
{
    cout << "\nАтака игрока:" << endl;
    InputHelper::waitForAttack();

    if (!checkHit(attacker.getDexterity(), target.getDexterity()))
    {
        displayAttackResult(AttackResult::MISS, 0, "Игрок");
        return AttackResult::MISS;
    }

    int damage = calculatePlayerDamage(attacker, target, turn);
    target.takeDamage(damage);
    attacker.onAttack(target, turn);

    displayAttackResult(AttackResult::HIT, damage, "Игрок");
    cout << "Здоровье противника: " << max(0, target.getCurrentHealth()) << endl;

    return AttackResult::HIT;
}

AttackResult CombatSystem::performEnemyAttack(Enemy &attacker, Character &target, int turn)
{
    cout << "\nАтака " << attacker.getName() << ":" << endl;
    attacker.incrementTurnCounter();

    if (!checkHit(attacker.getDexterity(), target.getDexterity()))
    {
        displayAttackResult(AttackResult::MISS, 0, attacker.getName());
        return AttackResult::MISS;
    }

    int damage = calculateEnemyDamage(attacker, target, turn);
    target.takeDamage(damage);

    displayAttackResult(AttackResult::HIT, damage, attacker.getName());
    cout << "Здоровье игрока: " << max(0, target.getCurrentHealth()) << endl;

    return AttackResult::HIT;
}

int CombatSystem::calculatePlayerDamage(const Character &attacker, const Enemy &target, int turn)
{
    int baseDamage = attacker.calculateAttackDamage();

    // Применяем модификаторы способностей персонажа
    int abilityModifiedDamage = attacker.modifyAttackDamageWithAbilities(baseDamage, target, turn);

    // Применяем эффекты оружия против врага
    int weaponModifiedDamage = applyWeaponEffects(abilityModifiedDamage, attacker.getWeapon(), target);

    // Применяем защитные способности врага
    return target.applyDefensiveEffects(weaponModifiedDamage, attacker.getWeapon().getType());
}

int CombatSystem::calculateEnemyDamage(const Enemy &attacker, const Character &target, int turn)
{
    int damage = attacker.calculateSpecialAttackDamage(turn);

    // Применяем защитные способности игрока
    return target.applyDefensiveEffects(damage, attacker);
}

bool CombatSystem::checkHit(int attackerDexterity, int targetDexterity)
{
    int hitChance = RandomGenerator::getInt(1, attackerDexterity + targetDexterity);
    return hitChance > targetDexterity;
}

int CombatSystem::applyWeaponEffects(int damage, const Weapon &weapon, const Enemy &target)
{
    // Скелет получает двойной урон от дробящего
    if (target.isVulnerableToCrushing() && weapon.getType() == WeaponType::CRUSHING)
    {
        damage *= 2;
        cout << "Скелет уязвим к дробящему! Урон удвоен!" << endl;
    }

    // Слайм невосприимчив к рубящему
    if (target.isImmuneToSlashing() && weapon.getType() == WeaponType::SLASHING)
    {
        damage -= weapon.getDamage();
        cout << "Слайм невосприимчив к рубящему! Урон от оружия заблокирован." << endl;
    }

    return max(0, damage);
}

bool CombatSystem::playerGoesFirst(const Character &player, const Enemy &enemy)
{
    return player.getDexterity() >= enemy.getDexterity();
}

void CombatSystem::displayTurnInfo(const Character &player, const Enemy &enemy, int turn)
{
    cout << "\n--- Ход " << turn << " ---" << endl;
    cout << "Игрок: " << player.getCurrentHealth() << "/" << player.getMaxHealth() << " HP" << endl;
    cout << enemy.getName() << ": " << enemy.getCurrentHealth() << " HP" << endl;
}

void CombatSystem::displayAttackResult(AttackResult result, int damage, const string &attackerName)
{
    if (result == AttackResult::MISS)
    {
        cout << "Промах!" << endl;
    }
    else
    {
        cout << "Нанесено " << damage << " урона!" << endl;
    }
}
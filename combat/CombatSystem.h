#pragma once
#include "../Character/Character.h"
#include "../Enemy/Enemy.h"

using namespace std;

enum class AttackResult
{
    MISS,
    HIT,
    CRITICAL
};

class CombatSystem
{
public:
    // Основная логика боя
    static bool executeBattle(Character &player, Enemy &enemy);

    // Выполнение атак
    static AttackResult performPlayerAttack(Character &attacker, Enemy &target, int turn);
    static AttackResult performEnemyAttack(Enemy &attacker, Character &target, int turn);

    // Расчет урона
    static int calculatePlayerDamage(const Character &attacker, const Enemy &target, int turn);
    static int calculateEnemyDamage(const Enemy &attacker, const Character &target, int turn);

    // Проверки попадания
    static bool checkHit(int attackerDexterity, int targetDexterity);

    // Применение эффектов
    static int applyWeaponEffects(int damage, const Weapon &weapon, const Enemy &target);

    // Определение порядка ходов
    static bool playerGoesFirst(const Character &player, const Enemy &enemy);

private:
    // Вспомогательные методы
    static void displayBattleStart(const Character &player, const Enemy &enemy);
    static void displayTurnInfo(const Character &player, const Enemy &enemy, int turn);
    static void displayAttackResult(AttackResult result, int damage, const string &attackerName);
};
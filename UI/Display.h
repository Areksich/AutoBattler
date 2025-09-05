#pragma once
#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Weapon.h"
#include <string>

using namespace std;

class Display
{
public:
    static void showGameIntro();
    static void showClassBonusesTable();
    static void showClassSelection();
    static void showCharacterStats(const Character &character);
    static void showBattleStart(const Character &player, const Enemy &enemy);
    static void showLevelUpPrompt();
    static void showVictoryMessage();
    static void showDefeatMessage();

    static bool offerWeapon(const Weapon &currentWeapon, const Weapon &newWeapon);

private:
    static void printSeparator(int length = 50);
    static void printTableRow(const string &col1, const string &col2, const string &col3, const string &col4);
};
#include "Display.h"
#include "../Utils/InputHelper.h"
#include "../Character/CharacterClass.h"
#include <iostream>
#include <iomanip>
#include <string>

void Display::showGameIntro()
{
    cout << "=== ПОШАГОВЫЙ АВТОБАТТЛЕР ===" << endl;
    cout << "\n=== ПОЖАЛУЙСТА, ВКЛЮЧИТЕ АНГЛИЙСКУЮ РАСКЛАДКУ ===" << endl;
}

void Display::showClassBonusesTable()
{
    cout << "\n=== БОНУСЫ КЛАССОВ ПО УРОВНЯМ ===" << endl;
    cout << "+" << string(69, '-') << "+" << endl;
    printTableRow("Класс", "Уровень 1", "Уровень 2", "Уровень 3");
    cout << "+" << string(69, '-') << "+" << endl;
    printTableRow("Разбойник", "Скрытая атака", "+1 Ловкость", "Яд (+1 урон/ход)");
    printTableRow("Воин", "Порыв к действию", "Щит (-3 урона)", "+1 Сила");
    printTableRow("Варвар", "Ярость (+2 урон)", "Каменная кожа", "+1 Выносливость");
    cout << "+" << string(69, '-') << "+" << endl;

    cout << "\nОписание способностей:" << endl;
    cout << "- Скрытая атака: +1 к наносимому урону, если ловкость персонажа > ловкости врага" << endl;
    cout << "- Порыв к действию: Двойной урон оружием в первом ходу боя" << endl;
    cout << "- Ярость: +2 урон первые 3 хода, затем -1 урон" << endl;
    cout << "- Щит: -3 получаемого урона, если сила персонажа > силы врага" << endl;
    cout << "- Каменная кожа: Урон снижается на значение выносливости" << endl;
    cout << "- Яд: Враг получает урон от яда в начале каждого хода, который увеличивается каждый ход на +1" << endl;
}

void Display::showClassSelection()
{
    cout << "\nВыберите класс:" << endl;
    cout << "1. Разбойник (4 HP/уровень, Кинжал)" << endl;
    cout << "2. Воин (5 HP/уровень, Меч)" << endl;
    cout << "3. Варвар (6 HP/уровень, Дубина)" << endl;
    cout << "Ваш выбор (1-3): ";
}

void Display::showCharacterStats(const Character &character)
{
    cout << "\n--- ХАРАКТЕРИСТИКИ ПЕРСОНАЖА ---" << endl;
    cout << "Общий уровень: " << character.getTotalLevel() << endl;
    cout << "Сила: " << character.getStrength()
         << " | Ловкость: " << character.getDexterity()
         << " | Выносливость: " << character.getEndurance() << endl;
    cout << "Здоровье: " << character.getCurrentHealth() << "/" << character.getMaxHealth() << endl;
    cout << "Оружие: ";
    character.getWeapon().displayInfo();
    cout << endl;

    cout << "\nАктивные способности:" << endl;
    character.displayAbilities();
}

void Display::showBattleStart(const Character &player, const Enemy &enemy)
{
    cout << "=== НОВЫЙ БОЙ ===" << endl;
    enemy.displayInfo();
    cout << endl;
}

void Display::showLevelUpPrompt()
{
    cout << "\n=== ПОВЫШЕНИЕ УРОВНЯ ===" << endl;
    showClassBonusesTable();

    cout << "\nВыберите класс для повышения уровня:" << endl;
    cout << "1. Разбойник" << endl;
    cout << "2. Воин" << endl;
    cout << "3. Варвар" << endl;
    cout << "Ваш выбор (1-3): ";
}

void Display::showVictoryMessage()
{
    cout << "Поздравляем! Вы прошли игру, победив 5 монстров подряд!" << endl;
}

void Display::showDefeatMessage()
{
    cout << "Поражение! Ваш персонаж погиб." << endl;
}

bool Display::offerWeapon(const Weapon &currentWeapon, const Weapon &newWeapon)
{
    cout << "\nНайдено оружие: ";
    newWeapon.displayInfo();
    cout << "\nТекущее оружие: ";
    currentWeapon.displayInfo();
    cout << "\n\nЗаменить оружие? (y/n): ";

    char choice = InputHelper::getYesNoChoice();
    if (choice == 'y' || choice == 'Y')
    {
        cout << "Оружие заменено на " << newWeapon.getName() << "!" << endl;
        return true;
    }
    return false;
}

void Display::printSeparator(int length)
{
    cout << string(length, '-') << endl;
}

void Display::printTableRow(const string &col1, const string &col2, const string &col3, const string &col4)
{
    cout << "| " << left << setw(10) << col1
         << " | " << setw(16) << col2
         << " | " << setw(16) << col3
         << " | " << setw(16) << col4 << " |" << endl;
}
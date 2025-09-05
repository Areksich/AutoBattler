#include "Game.h"
#include "Combat/CombatSystem.h"
#include "Utils/InputHelper.h"
#include "Utils/Random.h"
#include "UI/Display.h"
#include <iostream>
#include <cstdlib>

Game::Game() : currentState(GameState::CHARACTER_CREATION), monstersDefeated(0) {}

void Game::run()
{
    system("cls");
    Display::showGameIntro();

    while (true)
    {
        switch (currentState)
        {
        case GameState::CHARACTER_CREATION:
            handleCharacterCreation();
            break;
        case GameState::BATTLE:
            handleBattle();
            break;
        case GameState::LEVEL_UP:
            handleLevelUp();
            break;
        case GameState::VICTORY:
            handleVictory();
            return;
        case GameState::DEFEAT:
            handleDefeat();
            if (currentState == GameState::DEFEAT)
            {
                return;
            }
            break;
        }
    }
}

void Game::handleCharacterCreation()
{
    createNewCharacter();
    changeState(GameState::BATTLE);
}

void Game::handleBattle()
{
    if (monstersDefeated >= MONSTERS_TO_WIN)
    {
        changeState(GameState::VICTORY);
        return;
    }

    Enemy enemy = getRandomEnemy();

    system("cls");
    Display::showBattleStart(*player, enemy);

    if (CombatSystem::executeBattle(*player, enemy))
    {
        processVictory(enemy);
    }
    else
    {
        processDefeat();
    }
}

void Game::handleLevelUp()
{
    Display::showLevelUpPrompt();

    int choice = InputHelper::getValidChoice(1, 3);
    ClassType newClass = static_cast<ClassType>(choice - 1);

    player->levelUp(newClass);
    InputHelper::waitForSpacebar();

    changeState(GameState::BATTLE);
}

void Game::handleWeaponSelection(const Weapon &newWeapon)
{
    if (Display::offerWeapon(player->getWeapon(), newWeapon))
    {
        player->setWeapon(newWeapon);
    }
}

void Game::handleVictory()
{
    Display::showVictoryMessage();
    InputHelper::waitForSpacebar();
}

void Game::handleDefeat()
{
    Display::showDefeatMessage();

    if (wantsToPlayAgain())
    {
        monstersDefeated = 0;
        player.reset();
        changeState(GameState::CHARACTER_CREATION);
    }
}

void Game::createNewCharacter()
{
    player = make_unique<Character>();
    player->generateStats();

    Display::showClassBonusesTable();
    Display::showClassSelection();

    int choice = InputHelper::getValidChoice(1, 3);
    ClassType startClass = static_cast<ClassType>(choice - 1);

    player->initialize(startClass);

    InputHelper::waitForSpacebar();
}

Enemy Game::getRandomEnemy() const
{
    int index = RandomGenerator::getInt(0, 5); // 6 типов врагов
    return Enemy(static_cast<EnemyType>(index));
}

void Game::processVictory(const Enemy &defeatedEnemy)
{
    monstersDefeated++;
    cout << "Победа! Побеждено монстров: " << monstersDefeated << "/" << MONSTERS_TO_WIN << endl;

    // Проверяем, достигнута ли финальная победа
    if (monstersDefeated >= MONSTERS_TO_WIN)
    {
        changeState(GameState::VICTORY);
        return;
    }

    Weapon reward = WeaponFactory::getWeaponByName(defeatedEnemy.getReward());
    handleWeaponSelection(reward);

    // Если это не последний враг, продолжаем
    InputHelper::waitForSpacebar();
    system("cls");

    // Проверяем повышение уровня
    if (shouldLevelUp())
    {
        changeState(GameState::LEVEL_UP);
        return;
    }

    // Восстанавливаем здоровье после боя
    player->restoreHealth();
    cout << "Здоровье восстановлено!" << endl;

    // Переходим к следующему бою
    changeState(GameState::BATTLE);
}

void Game::processDefeat()
{
    changeState(GameState::DEFEAT);
}

bool Game::wantsToPlayAgain() const
{
    cout << "Хотите создать нового персонажа? (y/n): ";
    char choice = InputHelper::getYesNoChoice();
    system("cls");
    return choice == 'y' || choice == 'Y';
}
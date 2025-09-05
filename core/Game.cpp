#include "Game.h"

using namespace std;

    Game::Game() : monstersDefeated(0) {
        WeaponFactory::initializeWeapons();
    }
    
    void Game::run() {
        cout << "=== ПОШАГОВЫЙ АВТОБАТТЛЕР ===" << endl;
        
        while (true) {
            if (monstersDefeated == 0 || !player) {
                createNewPlayer();
            }
            
            if (monstersDefeated >= 5) {
                cout << "\n🎉 ПОЗДРАВЛЯЕМ! Игра пройдена! 🎉" << endl;
                cout << "Вы победили 5 монстров подряд!" << endl;
                break;
            }
            
            auto enemy = EnemyFactory::createRandomEnemy();
            cout << "\n=== НОВЫЙ ПРОТИВНИК ===" << endl;
            cout << "Встречен: " << enemy->getName() << endl;
            
            if (BattleSystem::fight(*player, *enemy)) {
                monstersDefeated++;
                cout << "\n✅ Победа! Побеждено монстров: " << monstersDefeated << "/5" << endl;
                
                player->restoreHealth();
                
                // Предложить оружие
                GameInterface::offerWeapon(*player, enemy->getReward());
                
                // Повысить уровень
                if (player->canLevelUp()) {
                    CharacterClass newClass = GameInterface::selectClass();
                    player->levelUp(newClass);
                }
                
            } else {
                cout << "\n💀 Поражение! Ваш персонаж погиб." << endl;
                monstersDefeated = 0;
                
                if (!GameInterface::askContinue()) {
                    break;
                }
            }
        }
    }
    
    void Game::createNewPlayer() {
        player = make_unique<Player>();
        CharacterClass startClass = GameInterface::selectClass();
        player->initialize(startClass);
    }
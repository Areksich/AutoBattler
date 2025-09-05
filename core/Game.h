#include "items/WeaponFactory.h"
#include "utils/GameInterface.h"
#include "combat/BattleSystem.h"
#include <iostream>

using namespace std;

class Game {    
public:
    Game();
    
    void run();
private:
    void createNewPlayer();

    unique_ptr<Player> player;
    int monstersDefeated;
};
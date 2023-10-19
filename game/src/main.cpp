#include "classes/ship/Ship.hpp"
#include "classes/board/Board.hpp"
#include "classes/game/Game.hpp"
#include <iostream>
#include <vector>

int main(){

    srand(time(nullptr));
    
    Game game;

    game.createGame();

    return 0;
}
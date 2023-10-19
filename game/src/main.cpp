#include "classes/ship/Ship.hpp"
#include "classes/board/Board.hpp"
#include "classes/game/Game.hpp"
#include <iostream>
#include <vector>

int main(){

    srand(time(nullptr));
    
    Game game;

    game.createGame();

    std::vector<int> shot = {2,3};

    std::cout << "Introduzca coordenadas: " << std::endl;
    std::cin >> shot[0];
    std::cin >> shot[1];

    if(game.shot(1, shot)){
        std::cout << "BOOOOOM" << std::endl;
    }else{
        std::cout << "AGUA" << std::endl;
    }

    return 0;
}
#include "classes/ship/Ship.hpp"
#include "classes/board/Board.hpp"
#include <iostream>
#include <vector>

int main(){
    Board b;

    std::cout << "Inicial board:" << std::endl;
    b.showBoard();
    std::cout << std::endl;

    Ship barquito(Type::LONG, Orientation::VERTICAL, {2, 2});

    if(b.addShip(barquito)){
        std::cout << "Added ship 1" << std::endl;
    } else {
        std::cout << "Could not add ship 1" << std::endl;
    }

    Ship barquito2(Type::LONG, Orientation::VERTICAL, {2, 4});

    if(b.addShip(barquito2)){
        std::cout << "Added ship 2" << std::endl;
    } else {
        std::cout << "Could not add ship 2" << std::endl;
    }

    Ship barquito3(Type::LONG, Orientation::HORIZONTAL, {0, 0});

    if(b.addShip(barquito3)){
        std::cout << "Added ship 3" << std::endl;
    } else {
        std::cout << "Could not add ship 3" << std::endl;
    }

    std::cout << "Final board:" << std::endl;
    b.showBoard();
    std::cout << std::endl;

    // b.setStartGame();
    // std::cout << "Inicial board:" << std::endl;
    // b.showBoard();
    // std::cout << std::endl;
    // std::cout << b.getShips() << std::endl;

    return 0;
}
#include "Game.hpp"
#include <iostream>

void Game::createGame(){

    std::cout << "Creating P1 board: " << std::endl;

    board1.setStartGame();

    board1.showBoard();

    std::cout << std::endl;

    std::cout << "Creating P2 board: " << std::endl;
    
    board2.setStartGame();

    board2.showBoard();

    std::cout << std::endl;

}
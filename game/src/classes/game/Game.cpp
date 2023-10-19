#include "Game.hpp"
#include <iostream>
#include <vector>

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

bool Game::shot(int player, std::vector<int> coords){
    if(player == 1){
        if(board1.getTable()[coords[1]][coords[0]] == 'B'){
            return true;
        }else{
            return false;
        }
    }else if(player == 2){
        if(board2.getTable()[coords[1]][coords[0]] == 'B'){
            return true;
        }else{
            return false;
        }
    }
}
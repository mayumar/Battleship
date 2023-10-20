#include "Game.hpp"
#include <iostream>
#include <vector>

void Game::createGame(){

    std::cout << "Creating P1 board: " << std::endl;

    board1.setStartGame();

    //board1.showBoard();

    std::cout << std::endl;

    std::cout << "Creating P2 board: " << std::endl;
    
    board2.setStartGame();

    //board2.showBoard();

    std::cout << std::endl;
}

bool Game::shot(int player, std::vector<int> shot){
    if(player == 1){
        if(board2.getTable()[shot[1]][shot[0]] == 'B'){            
            board2.setShot(shot);
            board2.showBoard();
            std::cout << "BOOOOOM" << std::endl;

            if(board2.isSinked(board2.findShip(shot))){
                std::cout << "SE HUNDIO" << std::endl;
                board2.sinkShip();
            }

            return true;
        }else{
            board2.setShot(shot);
            board2.showBoard();
            std::cout << "AGUA" << std::endl;
            return false;
        }

    }else if(player == 2){

        if(board1.getTable()[shot[1]][shot[0]] == 'B'){
            board1.setShot(shot);
            board1.showBoard();
            std::cout << "BOOOOOM" << std::endl;

            if(board1.isSinked(board1.findShip(shot))){
                std::cout << "SE HUNDIO" << std::endl;
                board1.sinkShip();
            }
 
            return true;
        }else{
            board1.setShot(shot);
            board1.showBoard();
            std::cout << "AGUA" << std::endl;
            return false;
        }

    }

    return false;
}
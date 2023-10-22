#include "Game.hpp"
#include <iostream>
#include <vector>

void Game::createGame(){

    std::cout << "Creating P1 board..." << std::endl;

    boardp1_.setStartGame();

    //board1.showBoard();

    std::cout << std::endl;

    std::cout << "Creating P2 board..." << std::endl;
    
    boardp2_.setStartGame();

    //board2.showBoard();

    std::cout << std::endl;
}

bool Game::shot(int player, std::vector<int> shot){
    if(player == 1){
        if(boardp2_.getTable()[shot[1]][shot[0]] == 'B'){            
            boardp2_.setShot(shot);
            p1game_.setShipShot(shot);
            p1game_.showBoard();
            std::cout << "BOOOOOM" << std::endl;

            if(boardp2_.isSinked(boardp2_.findShip(shot))){
                std::cout << "SE HUNDIO" << std::endl;
                boardp2_.sinkShip();
            }

            return true;
        }else{
            p1game_.setShot(shot);
            p1game_.showBoard();
            std::cout << "AGUA" << std::endl;
            return false;
        }

    }else if(player == 2){

        if(boardp1_.getTable()[shot[1]][shot[0]] == 'B'){            
            boardp1_.setShot(shot);
            p2game_.setShipShot(shot);
            p2game_.showBoard();
            std::cout << "BOOOOOM" << std::endl;

            if(boardp1_.isSinked(boardp1_.findShip(shot))){
                std::cout << "SE HUNDIO" << std::endl;
                boardp1_.sinkShip();
            }

            return true;
        }else{
            p2game_.setShot(shot);
            p2game_.showBoard();
            std::cout << "AGUA" << std::endl;
            return false;
        }

    }

    return false;
}
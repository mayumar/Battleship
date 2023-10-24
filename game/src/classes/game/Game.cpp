#include "Game.hpp"
#include "../../aux/aux.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sys/socket.h>

void Game::createGame(char * buffer, int &sizeBuffer){

    std::string stringBufferP1 = ("Creando tablero de " + p1_.getUsername() + "...\n\n");
    std::string stringBufferP2 = stringBufferP1;

    boardp1_.setStartGame();

    stringBufferP1 += boardp1_.showBoard();
    stringBufferP2 += ("Tablero de " + p1_.getUsername() + " creado\n");

    stringBufferP1 += ("Creando tablero de " + p2_.getUsername() + "...\n\n");
    stringBufferP2 += ("Creando tablero de " + p2_.getUsername() + "...\n\n");
    
    boardp2_.setStartGame();

    stringBufferP1 += ("Tablero de " + p2_.getUsername() + " creado\n");
    stringBufferP2 += boardp2_.showBoard();

    turn_ = 1;

    send(p1_.getSocket(), stringBufferP1.data(), stringBufferP1.length(), 0);
    send(p2_.getSocket(), stringBufferP2.data(), stringBufferP2.length(), 0);
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
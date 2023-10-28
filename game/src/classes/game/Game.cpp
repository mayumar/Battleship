#include "Game.hpp"
#include "../../aux/aux.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sys/socket.h>

void Game::createGame(int &sizeBuffer){

    std::string stringBufferP1 = "+Ok. Empieza la partida.";
    std::string stringBufferP2 = stringBufferP1;

    boardp1_.setStartGame();

    stringBufferP1 += boardp1_.showBoard();
    //boardp1_.showServerBoard();
    
    boardp2_.setStartGame();

    stringBufferP2 += boardp2_.showBoard();
    //boardp2_.showServerBoard();

    turn_ = 1;

    send(p1_.getSocket(), stringBufferP1.data(), sizeBuffer, 0);
    send(p2_.getSocket(), stringBufferP2.data(), sizeBuffer, 0);
}

bool Game::shot(std::vector<int> shot, std::string coords, int &sizeBuffer){
    std::string buffer;

    if(turn_ == 1){
        if(boardp2_.getTable()[shot[1]][shot[0]] == "B"){
            boardp2_.setShot(shot);
            //boardp2_.showServerBoard();
            //std::cout << "BOOOOOM" << std::endl;
            buffer = "+Ok. TOCADO: " + coords;

            if(boardp2_.isSinked(boardp2_.findShip(shot))){
                //std::cout << "SE HUNDIO" << std::endl;
                buffer = "+Ok. HUNDIDO: " + coords;
                boardp2_.sinkShip();
            }

            send(p1_.getSocket(), buffer.data(), sizeBuffer, 0);
            turn_ = 2;

            return true;
        }else{
            //boardp2_.showServerBoard();
            //std::cout << "AGUA" << std::endl;
            buffer = "+Ok. AGUA: " + coords;

            send(p1_.getSocket(), buffer.data(), sizeBuffer, 0);
            turn_ = 2;
            return false;
        }

        

    }else if(turn_ == 2){

        if(boardp1_.getTable()[shot[1]][shot[0]] == "B"){
            boardp1_.setShot(shot);
            //boardp1_.showServerBoard();
            //std::cout << "BOOOOOM" << std::endl;
            buffer = "+Ok. TOCADO: " + coords;

            if(boardp1_.isSinked(boardp1_.findShip(shot))){
                //std::cout << "SE HUNDIO" << std::endl;
                buffer = "+Ok. HUNDIDO: " + coords;
                boardp1_.sinkShip();
            }
            
            send(p2_.getSocket(), buffer.data(), sizeBuffer, 0);
            turn_ = 1;
            return true;
        }else{
            //boardp1_.showServerBoard();
            //std::cout << "AGUA" << std::endl;
            buffer = "+Ok. AGUA: " + coords;
            send(p2_.getSocket(), buffer.data(), sizeBuffer, 0);
            turn_ = 1;
            return false;
        }

        

    }

    return false;
}
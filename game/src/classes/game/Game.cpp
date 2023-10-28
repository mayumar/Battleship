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
    
    boardp2_.setStartGame();

    stringBufferP2 += boardp2_.showBoard();

    turn_ = 1;
    p1Shots_ = 0;
    p2Shots_ = 0;

    send(p1_.getSocket(), stringBufferP1.data(), sizeBuffer, 0);
    send(p2_.getSocket(), stringBufferP2.data(), sizeBuffer, 0);
}

bool Game::shot(std::vector<int> &shot, std::string &coords, int &sizeBuffer){
    std::string buffer;

    coords[0] = std::toupper(coords[0]);

    if(turn_ == 1){
        if(boardp2_.getTable()[shot[1]][shot[0]] == "B"){
            boardp2_.setShot(shot);
            buffer = "+Ok. TOCADO: " + coords;

            if(boardp2_.isSinked(boardp2_.findShip(shot))){
                buffer = "+Ok. HUNDIDO: " + coords;
                boardp2_.sinkShip();
            }
            send(p1_.getSocket(), buffer.data(), sizeBuffer, 0);

            p1Shots_++;
            return true;
        }else{
            buffer = "+Ok. AGUA: " + coords;
            send(p1_.getSocket(), buffer.data(), sizeBuffer, 0);

            turn_ = 2;
            p1Shots_++;

            return false;
        }

    }else if(turn_ == 2){

        if(boardp1_.getTable()[shot[1]][shot[0]] == "B"){
            boardp1_.setShot(shot);
            buffer = "+Ok. TOCADO: " + coords;

            if(boardp1_.isSinked(boardp1_.findShip(shot))){
                buffer = "+Ok. HUNDIDO: " + coords;
                boardp1_.sinkShip();
            }
            send(p2_.getSocket(), buffer.data(), sizeBuffer, 0);

            p2Shots_++;
            return true;
        }else{
            buffer = "+Ok. AGUA: " + coords;
            send(p2_.getSocket(), buffer.data(), sizeBuffer, 0);

            turn_ = 1;
            p2Shots_++;
            
            return false;
        }
    }

    return false;
}
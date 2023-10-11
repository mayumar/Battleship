#include <vector>
#include <iostream>
#include "Board.hpp"
#include "../ship/Ship.hpp"
#include "../../aux/aux.hpp"

Board::Board(){
    table_ = std::vector<std::vector<char>>(10, std::vector<char>(10, 'A'));
    ships_ = 0;
}

void Board::showBoard(){
    for(int i = 0; i < table_.size(); i++){
        for(int j = 0; j < table_[i].size(); j++){
            std::cout << table_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

//TODO: MEJORAR ESTO TAMBIEN
void Board::setStartGame(){
    std::vector <int> initCoordsShip(2);

    generateRandomCoords(initCoordsShip);
    Ship ship1(Type::LONG, Orientation::HORIZONTAL, initCoordsShip);
    addShip(ship1);

    generateRandomCoords(initCoordsShip);
    Ship ship2(Type::MEDIUM, Orientation::VERTICAL, initCoordsShip);
    addShip(ship2);

    generateRandomCoords(initCoordsShip);
    Ship ship3(Type::MEDIUM, Orientation::HORIZONTAL, initCoordsShip);
    addShip(ship3);

    generateRandomCoords(initCoordsShip);
    Ship ship4(Type::SHORT, Orientation::VERTICAL, initCoordsShip);
    addShip(ship4);

    generateRandomCoords(initCoordsShip);
    Ship ship5(Type::SHORT, Orientation::HORIZONTAL, initCoordsShip);
    addShip(ship5);
}

bool Board::checkShipPosition(Ship &ship){
    if (ship.getOrientation() == Orientation::VERTICAL){
        for(int row = ship.getCoordsEdge1()[0]; row < ship.getCoordsEdge2()[0]; row++){
            if(table_[row][ship.getCoordsEdge1()[1]+1] == 'B' || table_[row][ship.getCoordsEdge1()[1]-1] == 'B')
                return false;
        }
    } else {
        for(int col = ship.getCoordsEdge1()[1]; col < ship.getCoordsEdge2()[1]; col++){
            if(table_[ship.getCoordsEdge1()[0]+1][col] == 'B' || table_[ship.getCoordsEdge1()[0]-1][col] == 'B')
                return false;
        }
    }

    return true;
}

bool Board::addShip(Ship &newShip){
    //TODO: Hay que comprobar si el barco se puede poner en esa posicion
    if(!checkShipPosition(newShip))
        return false;
    
    if (newShip.getOrientation() == Orientation::VERTICAL) {
        for(int row = newShip.getCoordsEdge1()[0]; row < newShip.getCoordsEdge2()[0]; row++){
            table_[row][newShip.getCoordsEdge1()[1]] = 'B';
        }
    } else {
        for(int col = newShip.getCoordsEdge1()[1]; col < newShip.getCoordsEdge2()[1]; col++)
            table_[newShip.getCoordsEdge1()[0]][col] = 'B';
    }

    ships_++;

    return true;
}

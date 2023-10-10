#include "Board.hpp"
#include "../ship/Ship.hpp"
#include <vector>
#include <iostream>

void Board::showBoard(){
    for(int i = 0; i < table_.size(); i++){
        for(int j = 0; j < table_[i].size(); j++){
            std::cout << table_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool Board::addShip(Ship newShip){
    // for(int i = newShip.getCoordsEdge1()[0]; i < newShip.getCoordsEdge1()[1]; i++){

    // }
}

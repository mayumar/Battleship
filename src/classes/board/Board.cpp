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
            std::cout << table_[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

//TODO: MEJORAR ESTO TAMBIEN
void Board::setStartGame(){
    std::vector<int> initCords(2);
    Orientation orientation;
    bool flag = false;
    int o;

    std::cout << "Creating long ship..." << std::endl;

    do{
        o = rand()%2;
        if(o == 0){
            orientation = Orientation::HORIZONTAL;
        }else{
            orientation = Orientation::VERTICAL;
        }
        generateRandomCoords(initCords);
        
        Ship ship(Type::LONG, orientation, initCords);
        //if(flag){
            std::cout << "Barquito de tipo ";
            ship.printType();
            std::cout << " que está en ";
            ship.printOrientation();
            std::cout << " (" << ship.getCoordsEdge1()[0] << "," << ship.getCoordsEdge1()[1] << "),("
                    << ship.getCoordsEdge2()[0] << "," << ship.getCoordsEdge2()[1] << ")" << std::endl;
        //}
        
        flag = addShip(ship);


    }while(!flag);

    std::cout << "Creating medium ships..." << std::endl;

    for(int i = 0; i < 2; i++){
        flag = false;
        do{
            o = rand()%2;
            if(o == 0){
                orientation = Orientation::HORIZONTAL;
            }else{
                orientation = Orientation::VERTICAL;
            }
            generateRandomCoords(initCords);
            
            Ship ship(Type::MEDIUM, orientation, initCords);
            
            //if(flag){
                std::cout << "Barquito de tipo ";
                ship.printType();
                std::cout << " que está en ";
                ship.printOrientation();
                std::cout << " (" << ship.getCoordsEdge1()[0] << "," << ship.getCoordsEdge1()[1] << "),("
                        << ship.getCoordsEdge2()[0] << "," << ship.getCoordsEdge2()[1] << ")" << std::endl;
            //}
            
            flag = addShip(ship);

            
        }while(!flag);
    }
}

bool Board::checkShipPosition(Ship &ship){
    if (ship.getOrientation() == Orientation::VERTICAL){
        
        if(table_[ship.getCoordsEdge1()[1]][ship.getCoordsEdge1()[0]-1] == 'B')
            return false;
        
        if(table_[ship.getCoordsEdge2()[1]][ship.getCoordsEdge2()[0]+1] == 'B')
            return false;

        for(int row = ship.getCoordsEdge1()[0]; row < ship.getCoordsEdge2()[0]; row++){
            /*int coord = ship.getCoordsEdge1()[1]-1;
            
            if(coord < 0) coord = ship.getCoordsEdge1()[1];
            
            if(table_[ship.getCoordsEdge1()[1]+1][row] == 'B' || table_[coord][row] == 'B')
                return false;
            */
            int coord;

            coord = ship.getCoordsEdge1()[1]+1;
           
            if(coord < 10 && table_[coord][row] == 'B'){
                return false;
            }

            coord = ship.getCoordsEdge1()[1]-1;
           
            if(coord > 0 && table_[coord][row] == 'B'){
                return false;
            }
        
        }
    } else {

        if(table_[ship.getCoordsEdge1()[1]-1][ship.getCoordsEdge1()[0]] == 'B')
            return false;
        
        if(table_[ship.getCoordsEdge2()[1]+1][ship.getCoordsEdge2()[0]] == 'B')
            return false;

        for(int col = ship.getCoordsEdge1()[1]; col < ship.getCoordsEdge2()[1]; col++){
            /*
            int coord = ship.getCoordsEdge1()[0];
            
            if(coord < 0) coord = ship.getCoordsEdge1()[0]+1;

            if(table_[col][ship.getCoordsEdge1()[0]+1] == 'B' || table_[col][coord] == 'B')
                return false;
            */

            int coord;

            coord = ship.getCoordsEdge1()[0]+1;
           
            if(coord < 10 && table_[col][coord] == 'B'){
                return false;
            }

            coord = ship.getCoordsEdge1()[0]-1;
           
            if(coord > 0 && table_[col][coord] == 'B'){
                return false;
            }
    
        }
    }

    return true;
}

bool Board::addShip(Ship &newShip){
    
    if(newShip.getCoordsEdge2()[0] > 9 || newShip.getCoordsEdge2()[1] > 9){
        return false;
    }

    if(!checkShipPosition(newShip))
        return false;
    
    if (newShip.getOrientation() == Orientation::VERTICAL) {
        for(int row = newShip.getCoordsEdge1()[0]; row < newShip.getCoordsEdge2()[0]; row++){
            table_[newShip.getCoordsEdge1()[1]][row] = 'B';
        }
    } else {
        for(int col = newShip.getCoordsEdge1()[1]; col < newShip.getCoordsEdge2()[1]; col++)
            table_[col][newShip.getCoordsEdge1()[0]] = 'B';
    }

    ships_++;

    return true;
}

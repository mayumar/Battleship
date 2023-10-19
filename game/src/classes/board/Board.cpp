#include <vector>
#include <iostream>
#include "Board.hpp"
#include "../ship/Ship.hpp"
#include "../../aux/aux.hpp"

Board::Board(){
    table_ = std::vector<std::vector<char>>(10, std::vector<char>(10, 'A'));
    ships_ = std::vector<Ship>();
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

    std::cout << "Creating ships..." << std::endl << std::endl;;

    do{
        o = rand()%2;
        if(o == 0){
            orientation = Orientation::HORIZONTAL;
        }else{
            orientation = Orientation::VERTICAL;
        }
        generateRandomCoords(initCords);
        
        Ship ship(Type::LONG, orientation, initCords);
        if(flag){
            ship.printShip();
        }
        
        flag = addShip(ship);


    }while(!flag);

    //showBoard();

    //std::cout << "Creating medium ships..." << std::endl;

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
            
            if(flag){
                ship.printShip();
            }
            
            flag = addShip(ship);

            
        }while(!flag);

    //showBoard();

    }

    //std::cout << "Creating short ships..." << std::endl;

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
            
            Ship ship(Type::SHORT, orientation, initCords);
            
            if(flag){
                ship.printShip();
            }
            
            flag = addShip(ship);

            
        }while(!flag);

    //showBoard();

    }
}

bool Board::checkShipPosition(Ship &ship){
    int coord;

    if (ship.getOrientation() == Orientation::VERTICAL){

        coord = ship.getCoordsEdge1()[0]-1;
        
        if(coord >= 0 && table_[ship.getCoordsEdge1()[1]][coord] == 'B'){
            //std::cout << "B en (" << coord << "," << ship.getCoordsEdge1()[1] << ")" << std::endl;
            return false;
        }

        coord = ship.getCoordsEdge2()[0]+1;
        
        if(coord < 10 && table_[ship.getCoordsEdge2()[1]][coord] == 'B'){
            //std::cout << "B en (" << coord << "," << ship.getCoordsEdge2()[1] << ")" << std::endl;
            return false;
        }

        for(int row = ship.getCoordsEdge1()[0]; row <= ship.getCoordsEdge2()[0]; row++){

            if(table_[ship.getCoordsEdge1()[1]][row] == 'B'){
                //std::cout << "B en (" << row << "," << ship.getCoordsEdge1()[1] << ")" << std::endl;
                return false;
            }

            coord = ship.getCoordsEdge1()[1]+1;
           
            if(coord < 10 && table_[coord][row] == 'B'){
                //std::cout << "B en (" << row << "," << coord << ")" << std::endl;
                return false;
            }

            coord = ship.getCoordsEdge1()[1]-1;
           
            if(coord >= 0 && table_[coord][row] == 'B'){
                //std::cout << "B en (" << row << "," << coord << ")" << std::endl;
                return false;
            }
        
        }
    } else {

        coord = ship.getCoordsEdge1()[1]-1;

        if(coord >= 0 && table_[coord][ship.getCoordsEdge1()[0]] == 'B'){
            //std::cout << "B en (" << ship.getCoordsEdge1()[0] << "," << coord << ")" << std::endl;
            return false;
        }

        coord  = ship.getCoordsEdge2()[1]+1;
        
        if(coord < 10 && table_[coord][ship.getCoordsEdge2()[0]] == 'B'){
            //std::cout << "B en (" << ship.getCoordsEdge2()[0] << "," << coord << ")" << std::endl;
            return false;
        }

        for(int col = ship.getCoordsEdge1()[1]; col <= ship.getCoordsEdge2()[1]; col++){

            coord = ship.getCoordsEdge1()[0]+1;
           
            if(coord < 10 && table_[col][coord] == 'B'){
                //std::cout << "B en (" << coord << "," << col << ")" << std::endl;
                return false;
            }

            coord = ship.getCoordsEdge1()[0]-1;
           
            if(coord >= 0 && table_[col][coord] == 'B'){
                //std::cout << "B en (" << coord << "," << col << ")" << std::endl;
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
        for(int row = newShip.getCoordsEdge1()[0]; row <= newShip.getCoordsEdge2()[0]; row++){
            table_[newShip.getCoordsEdge1()[1]][row] = 'B';
        }
    } else {
        for(int col = newShip.getCoordsEdge1()[1]; col <= newShip.getCoordsEdge2()[1]; col++)
            table_[col][newShip.getCoordsEdge1()[0]] = 'B';
    }

    ships_.push_back(newShip);

    return true;
}

#include <vector>
#include <iostream>
#include "Board.hpp"
#include "../ship/Ship.hpp"
#include "../../aux/aux.hpp"

Board::Board(){
    table_ = std::vector<std::vector<char>>(10, std::vector<char>(10, '-'));
    ships_ = std::vector<Ship>();
    ships_alive_ = 0;
}

std::string Board::showBoard(){

    std::string out = "";

    out = "   │ A B C D E F G H I J │\n";
    out += "───┼─────────────────────┼─\n";

    for(int i = 0; i < table_.size(); i++){

        if(i != 9){
            out += (" " + std::to_string(i+1) + " │ ");
        }else{
            out += (std::to_string(i+1) + " │ ");
        }

        for(int j = 0; j < table_[i].size(); j++){
            char point = table_[j][i];
            out += (point + " ");
        }

        out += "│\n";
    }

    out += "───┼─────────────────────┼─\n";

    return out;

}

void Board::setStartGame(){
    std::vector<int> initCords(2);
    Orientation orientation;
    bool flag = false;
    int o;

    //std::cout << "Creating ships..." << std::endl << std::endl;

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
    ships_alive_++;

    return true;
}

void Board::setShot(std::vector<int> shot){
    for(int i = 0; i < table_.size(); i++){
        for(int j = 0; j < table_[i].size(); j++){
            if(i == shot[0] && j == shot[1]){
                table_[j][i] = 'X';
            }
        }
    }
}

void Board::setShipShot(std::vector<int> shot){
    for(int i = 0; i < table_.size(); i++){
        for(int j = 0; j < table_[i].size(); j++){
            if(i == shot[0] && j == shot[1]){
                table_[j][i] = 'T';
            }
        }
    }
}

Ship Board::findShip(std::vector<int> coords){

    for(int i = 0; i < ships_.size(); i++){
        for(int x = ships_[i].getCoordsEdge1()[0]; x <= ships_[i].getCoordsEdge2()[0]; x++){
            for(int y = ships_[i].getCoordsEdge1()[1]; y <= ships_[i].getCoordsEdge2()[1]; y++){
                if(coords[0] == x && coords[1] == y){
                    return ships_[i];
                }
            }
        }
    }

    return Ship();
}

bool Board::isSinked(Ship ship){
    int cont = 0;

    for(int x = ship.getCoordsEdge1()[0]; x <= ship.getCoordsEdge2()[0]; x++){
        for(int y = ship.getCoordsEdge1()[1]; y <= ship.getCoordsEdge2()[1]; y++){
            if(table_[y][x] == 'X'){
                cont++;
            }
        }
    }

    if(ship.getType() == Type::LONG && cont == 4){
        return true;
    }else if(ship.getType() == Type::MEDIUM && cont == 3){
        return true;
    }else if(ship.getType() == Type::SHORT && cont == 2){
        return true;
    }

    return false;
}
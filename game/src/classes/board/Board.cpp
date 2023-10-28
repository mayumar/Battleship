#include <vector>
#include <iostream>
#include "Board.hpp"
#include "../ship/Ship.hpp"
#include "../../aux/aux.hpp"

Board::Board(){
    table_ = std::vector<std::vector<std::string>>(10, std::vector<std::string>(10, "A"));
    ships_ = std::vector<Ship>();
    ships_alive_ = 0;
}

std::string Board::showBoard(){

    std::string out = "";

    for(int i = 0; i < table_.size(); i++){
        for(int j = 0; j < table_[i].size(); j++)
            out += table_[i][j];
        out += ";";
    }

    return out;

}

void Board::setStartGame(){
    std::vector<int> initCords(2);
    Orientation orientation;
    bool flag = false;
    int o;

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

    }

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

    }
}

bool Board::checkShipPosition(Ship &ship){
    int coord;

    if (ship.getOrientation() == Orientation::VERTICAL){

        coord = ship.getCoordsEdge1()[0]-1;
        
        if(coord >= 0 && table_[ship.getCoordsEdge1()[1]][coord] == "B"){
            return false;
        }

        coord = ship.getCoordsEdge2()[0]+1;
        
        if(coord < 10 && table_[ship.getCoordsEdge2()[1]][coord] == "B"){
            return false;
        }

        for(int row = ship.getCoordsEdge1()[0]; row <= ship.getCoordsEdge2()[0]; row++){

            if(table_[ship.getCoordsEdge1()[1]][row] == "B"){
                return false;
            }

            coord = ship.getCoordsEdge1()[1]+1;
           
            if(coord < 10 && table_[coord][row] == "B"){
                return false;
            }

            coord = ship.getCoordsEdge1()[1]-1;
           
            if(coord >= 0 && table_[coord][row] == "B"){
                return false;
            }
        
        }
    } else {

        coord = ship.getCoordsEdge1()[1]-1;

        if(coord >= 0 && table_[coord][ship.getCoordsEdge1()[0]] == "B"){
            return false;
        }

        coord  = ship.getCoordsEdge2()[1]+1;
        
        if(coord < 10 && table_[coord][ship.getCoordsEdge2()[0]] == "B"){
            return false;
        }

        for(int col = ship.getCoordsEdge1()[1]; col <= ship.getCoordsEdge2()[1]; col++){

            coord = ship.getCoordsEdge1()[0]+1;
           
            if(coord < 10 && table_[col][coord] == "B"){
                return false;
            }

            coord = ship.getCoordsEdge1()[0]-1;
           
            if(coord >= 0 && table_[col][coord] == "B"){
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
            table_[newShip.getCoordsEdge1()[1]][row] = "B";
        }
    } else {
        for(int col = newShip.getCoordsEdge1()[1]; col <= newShip.getCoordsEdge2()[1]; col++)
            table_[col][newShip.getCoordsEdge1()[0]] = "B";
    }

    ships_.push_back(newShip);
    ships_alive_++;

    return true;
}

void Board::setShot(std::vector<int> shot){
    for(int i = 0; i < table_.size(); i++){
        for(int j = 0; j < table_[i].size(); j++){
            if(i == shot[0] && j == shot[1]){
                table_[j][i] = "X";
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
            if(table_[y][x] == "X"){
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

//Esto se ha usado para hacer pruebas
void Board::showServerBoard(){
    std::cout << "   │ A B C D E F G H I J │ " << std::endl;
    std::cout << "───┼─────────────────────┼─" << std::endl;

    for(int i = 0; i < table_.size(); i++){

        if(i != 9){
            std::cout << " " << i+1 << " │ ";
        }else{
            std::cout << i+1 << " │ ";
        }

        for(int j = 0; j < table_[i].size(); j++){
            std::cout << table_[j][i] << " ";
        }

        std::cout << "│" << std::endl;
    }

    std::cout << "───┼─────────────────────┼─" << std::endl << std::endl;
}
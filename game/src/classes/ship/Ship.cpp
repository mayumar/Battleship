#include "Ship.hpp"

Ship::Ship(Type type, Orientation orientation, std::vector<int> coordsEdge1){
    type_ = type;
    orientation_ = orientation;
    coordsEdge1_ = coordsEdge1;
    coordsEdge2_ = std::vector<int>(2);
    
    if(type_ == Type::LONG){
        if(orientation_ == Orientation::HORIZONTAL){
            coordsEdge2_[0] = coordsEdge1_[0];
            coordsEdge2_[1] = coordsEdge1_[1]+3;
        }else{
            coordsEdge2_[0] = coordsEdge1_[0]+3;
            coordsEdge2_[1] = coordsEdge1_[1];
        }
    }else if(type_ == Type::MEDIUM){
        if(orientation_ == Orientation::HORIZONTAL){
            coordsEdge2_[0] = coordsEdge1_[0];
            coordsEdge2_[1] = coordsEdge1_[1]+2;
        }else{
            coordsEdge2_[0] = coordsEdge1_[0]+2;
            coordsEdge2_[1] = coordsEdge1_[1];
        }
    }else{
        if(orientation_ == Orientation::HORIZONTAL){
            coordsEdge2_[0] = coordsEdge1_[0];
            coordsEdge2_[1] = coordsEdge1_[1]+1;
        }else{
            coordsEdge2_[0] = coordsEdge1_[0]+1;
            coordsEdge2_[1] = coordsEdge1_[1];
        }
    }
}

void Ship::printType(){
    if(type_ == Type::LONG){
        std::cout << "long";
    }else if(type_ == Type::MEDIUM){
        std::cout << "medium";
    }else{
        std::cout << "short";
    }
}

void Ship::printOrientation(){
    if(orientation_ == Orientation::VERTICAL){
        std::cout << "vertical";
    }else{
        std::cout << "horizontal";
    }
}

void Ship::printShip(){
    std::cout << "Barquito de tipo ";
    printType();
    std::cout << " que está en ";
    printOrientation();
    std::cout << " (" << getCoordsEdge1()[0] << "," << getCoordsEdge1()[1] << "),("
            << getCoordsEdge2()[0] << "," << getCoordsEdge2()[1] << ")" << std::endl;
}

#include "Ship.hpp"

Ship::Ship(Type type, Orientation orientation, std::vector<int> coordsEdge1):
            type_(type), orientation_(orientation), coordsEdge1_(coordsEdge1){
    if(type == Type::LONG){
        if(orientation == Orientation::HORIZONTAL){
            coordsEdge2_[0] = coordsEdge1[0]+4;
            coordsEdge2_[1] = coordsEdge1[1];
        }else{
            coordsEdge2_[0] = coordsEdge1[0];
            coordsEdge2_[1] = coordsEdge1[1]+4;
        }
    }else if(type == Type::MEDIUM){
        if(orientation == Orientation::HORIZONTAL){
            coordsEdge2_[0] = coordsEdge1[0]+3;
            coordsEdge2_[1] = coordsEdge1[1];
        }else{
            coordsEdge2_[0] = coordsEdge1[0];
            coordsEdge2_[1] = coordsEdge1[1]+3;
        }
    }else{
        if(orientation == Orientation::HORIZONTAL){
            coordsEdge2_[0] = coordsEdge1[0]+2;
            coordsEdge2_[1] = coordsEdge1[1];
        }else{
            coordsEdge2_[0] = coordsEdge1[0];
            coordsEdge2_[1] = coordsEdge1[1]+2;
        }
    }
}

void Ship::printType(){
    if(type_ == Type::LONG){
        std::cout << "long";
    }
}

void Ship::printOrientation(){
    if(orientation_ == Orientation::VERTICAL){
        std::cout << "vertical";
    }
}

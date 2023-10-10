#include "Ship.hpp"

Ship::Ship(Type type, Orientation orientation, std::tuple<char, int> coordsEdge1):
            type_(type), orientation_(orientation), coordsEdge1_(coordsEdge1){
    if(type == Type::LONG){
        if(orientation == Orientation::HORIZONTAL){
            coordsEdge2_ = std::make_tuple(std::get<char>(coordsEdge1)+4, std::get<int>(coordsEdge1));
        }else{
            coordsEdge2_ = std::make_tuple(std::get<char>(coordsEdge1), std::get<int>(coordsEdge1)+4);
        }
    }else if(type == Type::MEDIUM){
        if(orientation == Orientation::HORIZONTAL){
            coordsEdge2_ = std::make_tuple(std::get<char>(coordsEdge1)+3, std::get<int>(coordsEdge1));
        }else{
            coordsEdge2_ = std::make_tuple(std::get<char>(coordsEdge1), std::get<int>(coordsEdge1)+3);
        }
    }else{
        if(orientation == Orientation::HORIZONTAL){
            coordsEdge2_ = std::make_tuple(std::get<char>(coordsEdge1)+2, std::get<int>(coordsEdge1));
        }else{
            coordsEdge2_ = std::make_tuple(std::get<char>(coordsEdge1), std::get<int>(coordsEdge1)+2);
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

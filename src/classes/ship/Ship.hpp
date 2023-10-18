#ifndef SHIP_HPP
#define SHIP_HPP

#include <vector>
#include <iostream>

enum class Orientation{
    HORIZONTAL, 
    VERTICAL
};

enum class Type{
    LONG,
    MEDIUM,
    SHORT
};

class Ship{
    private:
        Type type_;
        Orientation orientation_;
        std::vector<int> coordsEdge1_;
        std::vector<int> coordsEdge2_;

    public:
        Ship(Type type, Orientation orientation, std::vector<int> coordsEdge1);

        inline Type getType(){return type_;}
        inline Orientation getOrientation(){return orientation_;}
        inline std::vector<int> getCoordsEdge1(){return coordsEdge1_;}
        inline std::vector<int> getCoordsEdge2(){return coordsEdge2_;}

        void printType();
        void printOrientation();
        void printShip();
};

#endif
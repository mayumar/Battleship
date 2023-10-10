#ifndef SHIP_HPP
#define SHIP_HPP

#include <tuple>
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
        std::tuple<char, int> coordsEdge1_;
        std::tuple<char, int> coordsEdge2_;

    public:
        Ship(Type type, Orientation orientation, std::tuple<char, int> coordsEdge1);

        inline Type getType(){return type_;}
        inline Orientation getOrientation(){return orientation_;}
        inline std::tuple<char,int> getCoordsEdge1(){return coordsEdge1_;}
        inline std::tuple<char,int> getCoordsEdge2(){return coordsEdge2_;}

        void printType();
        void printOrientation();

};

#endif
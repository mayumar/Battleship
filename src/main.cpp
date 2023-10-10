#include "classes/ship/Ship.hpp"
#include "classes/board/Board.hpp"
#include <iostream>
#include <vector>

int main(){
    Board b;

    b.showBoard();

    Ship barquito(Type::LONG, Orientation::VERTICAL, {'A', 1});

    b.addShip(barquito);

    b.showBoard();

    // std::cout << "Hola, soy un barquito de tipo ";
    // barquito.printType();
    // std::cout << " que esta en ";
    // barquito.printOrientation();
    //std::cout << " y mis coordenadas son desde (" << barquito.getCoordsEdge1() << ") hasta (" << barquito.getCoordsEdge2() <<")" << std::endl;

    return 0;
}
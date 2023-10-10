#include "classes/Ship.hpp"
#include <iostream>
#include <vector>

int main(){
    std::vector<std::vector<char>> table(10, std::vector<char>(10, 'A'));

    for(int i = 0; i < table.size(); i++){
        for(int j = 0; j < table[i].size(); j++){
            std::cout << table[i][j] << " ";
        }
        std::cout << std::endl;
    }

    Ship barquito(Type::LONG, Orientation::VERTICAL, {'A', 1});

    std::cout << "Hola, soy un barquito de tipo ";
    barquito.printType();
    std::cout << " que esta en ";
    barquito.printOrientation();
    //std::cout << " y mis coordenadas son desde (" << barquito.getCoordsEdge1() << ") hasta (" << barquito.getCoordsEdge2() <<")" << std::endl;

    return 0;
}
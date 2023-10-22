#include <ctime>
#include <vector>
#include <iostream>

#include "aux.hpp"

void generateRandomCoords(std::vector<int> &coords){
    for(int i = 0; i < 2; i++)
        coords[i] = std::rand() % 10;
}

void cleanString(std::string &cad){
    std::string cleanCad = cad;
    cad = "";
    
    for (char c : cleanCad) {
        if (c != '\n' && c != '\r') 
            cad += c;
    }
}
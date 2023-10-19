#include <ctime>
#include <vector>
#include <iostream>

void generateRandomCoords(std::vector<int> &coords){
    for(int i = 0; i < 2; i++)
        coords[i] = std::rand() % 10;
}

std::string cleanString(std::string &cad){
    std::string cleanCad;
    
    for (char c : cad) {
        if (c != '\n' && c != '\r') 
            cleanCad += c;
    }

    return cleanCad;
}
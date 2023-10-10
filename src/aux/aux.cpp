#include <ctime>
#include <vector>
#include <iostream>

void generateRandomCoords(std::vector<int> &coords){
    std::srand(std::time(nullptr));
    for(int i = 0; i < 2; i++){
        coords[i] = std::rand() % 11;
    }
}
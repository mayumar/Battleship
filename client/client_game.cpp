#include "client_game.hpp"
#include <map>
#include <sstream>

void parseBoard(std::string &table, std::vector<std::vector<std::string>> &board) {
    std::vector<std::string> row;
    std::string elem;

    for (char c : table) {
        elem = std::string(1, c);
        if (c == ';') {
            board.push_back(row);
            row.clear();
        } else {
            row.push_back(elem);
        }
    }
}

std::string showBoard(std::vector<std::vector<std::string>> &board) {
    std::string out = "";

    out = "   │ A B C D E F G H I J │\n";
    out += "───┼─────────────────────┼─\n";

    for(int i = 0; i < board.size(); i++){

        if(i != 9){
            out += (" " + std::to_string(i+1) + " │ ");
        }else{
            out += (std::to_string(i+1) + " │ ");
        }

        for(int j = 0; j < board[i].size(); j++){
            std::string point = board[j][i];
            out += (point + " ");
        }

        out += "│\n";
    }

    out += "───┼─────────────────────┼─\n";

    return out;
}

void getCoords(std::string coords, std::vector<int> &shot){
    
    std::map<std::string, int> coordsMap = {
        {"A", 0},
        {"B", 1},
        {"C", 2},
        {"D", 3},
        {"E", 4},
        {"F", 5},
        {"G", 6},
        {"H", 7},
        {"I", 8},
        {"J", 9},
    };

    std::string word, numSTR;
    std::istringstream ss(coords);
    std::getline(ss, word, ',');
    std::getline(ss, numSTR);
    int num = std::stoi(numSTR);

    shot = {num-1, coordsMap[word]};
    
}
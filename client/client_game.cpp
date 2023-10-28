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

void sinkShip(std::vector<std::vector<std::string>> &board, std::vector<int> &lastShot){
    bool vertical = false;
    if(lastShot[0] > 0 && board[lastShot[1]][lastShot[0]-1] == "X"){
        vertical = true;
    }else if(lastShot[0] < 9 && board[lastShot[1]][lastShot[0]+1] == "X"){
        vertical = true;
    }
    
    if(vertical){
        for(int i = lastShot[0]; i >= 0 && board[lastShot[1]][i] == "X"; i--){
            board[lastShot[1]][i] = "◉";
        }

        for(int i = lastShot[0]; i < 10 && board[lastShot[1]][i] == "X"; i++){
            board[lastShot[1]][i] = "◉";
        }
    }else{
        for(int i = lastShot[1]; i >= 0 && board[i][lastShot[0]] == "X"; i--){
            board[i][lastShot[0]] = "◉";
        }

        for(int i = lastShot[1]; i < 10 && board[i][lastShot[0]] == "X"; i++){
            board[i][lastShot[1]] = "◉";
        }
    }
}

bool isSinked(std::vector<std::vector<std::string>> &board, std::vector<int> &lastShot){
    if(lastShot[0] > 0 && board[lastShot[1]][lastShot[0]-1] == "B"){
        return false;
    }else if(lastShot[0] < 9 && board[lastShot[1]][lastShot[0]+1] == "B"){
        return false;
    }else if(lastShot[1] > 0 && board[lastShot[1]-1][lastShot[0]] == "B"){
        return false;
    }else if(lastShot[1] < 9 && board[lastShot[1]+1][lastShot[0]] == "B"){
        return false;
    }

    bool vertical = false;
    if(lastShot[0] > 0 && board[lastShot[1]][lastShot[0]-1] == "X"){
        vertical = true;
    }else if(lastShot[0] < 9 && board[lastShot[1]][lastShot[0]+1] == "X"){
        vertical = true;
    }

    if(vertical){
        for(int i = lastShot[0]; i >= 0 && board[lastShot[1]][i] != "-" && board[lastShot[1]][i] != "A"; i--){
            if(board[lastShot[1]][i] == "B"){
                return false;
            }
        }

        for(int i = lastShot[0]; i < 10 && board[lastShot[1]][i] != "-" && board[lastShot[1]][i] != "A"; i++){
            if(board[lastShot[1]][i] == "B"){
                return false;
            }
        }
    }else{
        for(int i = lastShot[1]; i >= 0 && board[i][lastShot[0]] != "-" && board[i][lastShot[0]] != "A"; i--){
            if(board[i][lastShot[0]] == "B"){
                return false;
            }
        }

        for(int i = lastShot[1]; i < 10 && board[i][lastShot[0]] != "-" && board[i][lastShot[0]] != "A"; i++){
            if(board[i][lastShot[0]] == "B"){
                return false;
            }
        }
    }

    return true;
}
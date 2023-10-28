#include "board_manager.hpp"
#include "client_game.hpp"
#include <iostream>

void manageReponse(std::string &stringBuffer, std::vector<std::vector<std::string>> &board){
    std::string waterString = "+Ok. AGUA: ";
    std::string hittedString = "+Ok. TOCADO: ";
    std::string sinkedString = "+Ok. HUNDIDO: ";
    size_t pos;
    std::vector<int> shot(2);
    

    if((pos = stringBuffer.find(waterString)) != std::string::npos){
        
        std::cout << stringBuffer << std::endl << std::endl;
        std::string coords = stringBuffer.substr(pos + waterString.length());
        getCoords(coords, shot);

        if(board[shot[1]][shot[0]] == "-")
            board[shot[1]][shot[0]] = "A";

        stringBuffer = showBoard(board);

    }else if((pos = stringBuffer.find(hittedString)) != std::string::npos){
        
        std::cout << stringBuffer << std::endl << std::endl;
        std::string coords = stringBuffer.substr(pos + hittedString.length());
        getCoords(coords, shot);
        board[shot[1]][shot[0]] = "X";
        stringBuffer = showBoard(board);

    }else if((pos = stringBuffer.find(sinkedString)) != std::string::npos){
        
        std::cout << stringBuffer << std::endl << std::endl;
        std::string coords = stringBuffer.substr(pos + sinkedString.length());
        getCoords(coords, shot);
        board[shot[1]][shot[0]] = "X";
        sinkShip(board, shot);
        stringBuffer = showBoard(board);

    }
}
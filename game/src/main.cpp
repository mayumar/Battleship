#include "classes/ship/Ship.hpp"
#include "classes/board/Board.hpp"
#include "classes/game/Game.hpp"
#include "server/server.hpp"
#include "auth/auth.hpp"
#include <iostream>
#include <vector>

int main(){
    srand(time(nullptr));
    // Game game;
    // game.createGame();


    // std::vector<int> shot(2);
    // int player = 0;

    // while(game.getBoardp1().getshipsAlive() > 0 && game.getBoardp2().getshipsAlive() > 0){
    //     player++;
        
    //     std::cout << "Turno del jugador " << player << std::endl;
        
    //     if(player == 1){
    //         game.getP1Game().showBoard();
    //     }else{
    //         game.getP2Game().showBoard();
    //     }

    //     std::cout << "Jugador " << player << " introduzca coordenadas: " << std::endl;
    //     std::cin >> shot[0];
    //     std::cin >> shot[1];

    //     game.shot(player, shot);

    //     if(game.getBoardp1().getshipsAlive() == 0){
    //         std::cout << "Gano el jugador 2" << std::endl;
    //     }else if(game.getBoardp2().getshipsAlive() == 0){
    //         std::cout << "Gano el jugador 1" << std::endl;
    //     }

    //     player %= 2;
    // }

    setServer();
    
    return 0;
}
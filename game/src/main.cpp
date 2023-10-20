#include "classes/ship/Ship.hpp"
#include "classes/board/Board.hpp"
#include "classes/game/Game.hpp"
#include <iostream>
#include <vector>

int main(){

    srand(time(nullptr));
    
    Game game;

    game.createGame();

    std::vector<int> shot(2);
    int player = 0;

    while(game.getBoard1().getshipsAlive() > 0 && game.getBoard2().getshipsAlive() > 0){
        std::cout << "Jugador " << 1+(player%2) << " introduzca coordenadas: " << std::endl;
        std::cin >> shot[0];
        std::cin >> shot[1];

        game.shot(1+(player%2), shot);

        if(game.getBoard1().getshipsAlive() == 0){
            std::cout << "Gano el jugador 1" << std::endl;
        }else if(game.getBoard2().getshipsAlive() == 0){
            std::cout << "Gano el jugador 2" << std::endl;
        }

        player++;
    }

    return 0;
}
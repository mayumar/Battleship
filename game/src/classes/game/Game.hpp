#ifndef GAME_HPP
#define GAME_HPP

#include "../board/Board.hpp"
#include <vector>

class Game{
    private:
        Board board1;
        Board board2;
    public:
        inline Game(){board1 = Board(); board2 = Board();};

        void createGame();

        bool shot(int player, std::vector<int> coords);

};

#endif
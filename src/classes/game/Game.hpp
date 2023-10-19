#ifndef GAME_HPP
#define GAME_HPP

#include "../board/Board.hpp"

class Game{
    private:
        Board board1;
        Board board2;
    public:
        inline Game(){board1 = Board(); board2 = Board();};

        void createGame();

};

#endif
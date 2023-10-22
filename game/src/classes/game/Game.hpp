#ifndef GAME_HPP
#define GAME_HPP

#include "../board/Board.hpp"
#include <vector>

class Game{
    private:
        Board boardp1_;
        Board boardp2_;
        Board p1game_;
        Board p2game_;
        
    public:
        inline Game() {};
        inline Board getBoardp1(){return boardp1_;}
        inline Board getBoardp2(){return boardp2_;}
        inline Board getP1Game(){return p1game_;}
        inline Board getP2Game(){return p2game_;}

        void createGame();

        bool shot(int player, std::vector<int> shot);
};

#endif
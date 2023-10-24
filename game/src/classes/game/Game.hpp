#ifndef GAME_HPP
#define GAME_HPP

#include "../board/Board.hpp"
#include "../player/Player.hpp"
#include <vector>

class Game{
    private:
        Player p1_;
        Player p2_;
        Board boardp1_;
        Board boardp2_;
        int turn_;
        
    public:
        inline Game() {};
        inline Board getBoardp1(){return boardp1_;}
        inline Board getBoardp2(){return boardp2_;}
        inline Player getP1(){return p1_;}
        inline Player getP2(){return p2_;}
        inline int getTurn(){return turn_;}

        inline void setP1(Player p1){p1_ = p1;}
        inline void setP2(Player p2){p2_ = p2;}

        void createGame(int &sizeBuffer);

        bool shot(std::vector<int> shot, std::string coords, int &sizeBuffer);
};

#endif
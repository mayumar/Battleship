#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "../ship/Ship.hpp"

class Board {
    private:
        std::vector<std::vector<char>> table_;

    public:
        inline Board(){ table_ = std::vector<std::vector<char>>(10, std::vector<char>(10, 'A')); }
        void showBoard();
        bool addShip(Ship newShip);
};

#endif
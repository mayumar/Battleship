#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "../ship/Ship.hpp"

class Board {
    private:
        std::vector<std::vector<char>> table_;
        int ships_;

    protected:
        bool checkShipPosition(Ship &ship);
        bool addShip(Ship &newShip);

    public:
        Board();
        inline void setShips(int ships){ships_ = ships;}
        inline int getShips(){return ships_;}
        void showBoard();
        void setStartGame();
        
};

#endif
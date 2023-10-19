#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "../ship/Ship.hpp"

class Board {
    private:
        std::vector<std::vector<char>> table_;
        std::vector<Ship> ships_;

    protected:
        bool checkShipPosition(Ship &ship);
        bool addShip(Ship &newShip);

    public:
        Board();
        inline std::vector<Ship> getShips(){return ships_;}
        inline std::vector<std::vector<char>> getTable(){return table_;};
        void showBoard();
        void setStartGame();
        
};

#endif
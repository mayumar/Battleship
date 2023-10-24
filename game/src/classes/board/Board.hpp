#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>
#include "../ship/Ship.hpp"

class Board {
    private:
        std::vector<std::vector<char>> table_;
        std::vector<Ship> ships_;
        int ships_alive_;

    protected:
        bool checkShipPosition(Ship &ship);
        bool addShip(Ship &newShip);

    public:
        Board();
        inline std::vector<Ship> getShips(){return ships_;}
        inline std::vector<std::vector<char>> getTable(){return table_;}
        inline int getshipsAlive() {return ships_alive_;}
        inline void sinkShip() {ships_alive_--;}
        std::string showBoard();
        void setStartGame();
        void setShot(std::vector<int> shot);
        void setShipShot(std::vector<int> shot);
        Ship findShip(std::vector<int> coords);
        bool isSinked(Ship ship);
        
};

#endif
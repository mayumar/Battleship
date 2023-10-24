#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>
#include "../ship/Ship.hpp"

class Board {
    private:
        std::vector<std::vector<std::string>> table_;
        std::vector<Ship> ships_;
        int ships_alive_;

    protected:
        bool checkShipPosition(Ship &ship);
        bool addShip(Ship &newShip);

    public:
        Board();
        inline std::vector<Ship> getShips(){return ships_;}
        inline std::vector<std::vector<std::string>> getTable(){return table_;}
        inline int getshipsAlive() {return ships_alive_;}
        inline void sinkShip() {ships_alive_--;}
        std::string showBoard();
        void setStartGame();
        void setShot(std::vector<int> shot);
        Ship findShip(std::vector<int> coords);
        bool isSinked(Ship ship);

        void showServerBoard();
        
};

#endif
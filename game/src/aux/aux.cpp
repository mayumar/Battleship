#include <ctime>
#include <vector>
#include <iostream>
#include <list>

#include "aux.hpp"
#include "../classes/player/Player.hpp"

void generateRandomCoords(std::vector<int> &coords){
    for(int i = 0; i < 2; i++)
        coords[i] = std::rand() % 10;
}

void cleanString(std::string &cad){
    std::string cleanCad = cad;
    cad = "";
    
    for (char c : cleanCad) {
        if (c != '\n' && c != '\r') 
            cad += c;
    }
}

/*
void addLoginPlayer(std::list<Player> &loginPlayers, Player &player){
    if(!player.isLogin()) return;
    loginPlayers.push_back(player);
}
*/

Player searchPlayer(std::list<Player> &players, int sd){
    for(auto p : players)
        if(p.getSocket() == sd) return p;

    return Player();
}

std::list<Player>::iterator findInList(std::list<Player> &players, Player p){
    std::list<Player>::iterator it;
    
    for(it = players.begin(); it != players.end(); it++){
        if(it->getSocket() == p.getSocket()){
            return it;
        }
    }

    return players.end();
}

void removePlayerFromList(std::list<Player> &players, int &sd){
    auto p = searchPlayer(players, sd);
    if(p.getUsername() == "" || p.getPassword() == "") return;
    players.remove(p);
}
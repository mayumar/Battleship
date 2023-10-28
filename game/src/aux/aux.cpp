#include <ctime>
#include <vector>
#include <iostream>
#include <list>
#include <queue>

#include "aux.hpp"
#include "../classes/player/Player.hpp"
#include "../classes/game/Game.hpp"

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

void upper(std::string &s){
    for(int i = 0; i < s.size(); i++) 
        s[i] = std::toupper(s[i]);
}

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

std::list<Game>::iterator findInList(std::list<Game> &games, Player p){
    std::list<Game>::iterator it;

    for(it = games.begin(); it != games.end(); it++){
        if(it->getP1() == p){
            return it;
        }else if(it->getP2() == p){
            return it;
        }
    }

    return games.end();
}

void removePlayerFromList(std::list<Player> &players, int &sd){
    auto p = searchPlayer(players, sd);
    if(p.getUsername() == "" || p.getPassword() == "") return;
    players.remove(p);
}

void removeGameFromList(std::list<Game> &games, Player p){
    auto g = findInList(games, p);
    games.erase(g);
}

bool isInQueue(std::queue<Player> &waitingPlayers, int &socket){
    auto tempQueue = waitingPlayers;
    
    while(!tempQueue.empty()){
        auto pAux = tempQueue.front();
        tempQueue.pop();
        if(pAux.getSocket() == socket)
            return true;
    }

    return false;
}

void removeFromQueue(std::queue<Player> &waitingPlayers, int &socket){
    std::queue<Player> tempQueue;
    while(!waitingPlayers.empty()){
        auto pAux = waitingPlayers.front();
        waitingPlayers.pop();
        if(pAux.getSocket() != socket) 
            tempQueue.push(pAux);
    }

    waitingPlayers = tempQueue;
}
#ifndef AUX_HPP
#define AUX_HPP

#include <ctime>
#include <vector>
#include <list>
#include <queue>

#include "../classes/player/Player.hpp"
#include "../classes/game/Game.hpp"

void generateRandomCoords(std::vector<int> &coords);
void cleanString(std::string &cad);
void upper(std::string &s);
//void addLoginPlayer(std::list<Player> &loginPlayers, Player &player);
Player searchPlayer(std::list<Player> &players, int sd);
void removePlayerFromList(std::list<Player> &players, int &sd);
std::list<Player>::iterator findInList(std::list<Player> &players, Player p);
std::list<Game>::iterator findInList(std::list<Game> &games, Player p);

bool isInQueue(std::queue<Player> &waitingPlayers, int &socket);
void removeFromQueue(std::queue<Player> &waitingPlayers, int &socket);

#endif
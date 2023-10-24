#ifndef AUX_HPP
#define AUX_HPP

#include <ctime>
#include <vector>
#include <list>

#include "../classes/player/Player.hpp"

void generateRandomCoords(std::vector<int> &coords);
void cleanString(std::string &cad);
void addLoginPlayer(std::list<Player> &loginPlayers, Player &player);
Player searchPlayer(std::list<Player> &loginPlayers, int sd);

#endif
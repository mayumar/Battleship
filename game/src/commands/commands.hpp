#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <queue>
#include <map>

#include "../classes/player/Player.hpp"
#include "../classes/game/Game.hpp"

void managedCommand(char *buffer, int &sizeBuffer, int &client, Player &p, Player &p2, 
                    std::queue<Player> &players);

#endif
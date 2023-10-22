#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <queue>
#include "../classes/player/Player.hpp"
#include "../classes/game/Game.hpp"

void managedCommand(char *buffer, int &sizeBuffer, int &client, Player &p, std::queue<Player> &players, Game &game);

#endif
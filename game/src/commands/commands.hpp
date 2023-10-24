#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <queue>
#include <list>

#include "../classes/player/Player.hpp"
#include "../classes/game/Game.hpp"

void managedCommand(char *buffer, int &sizeBuffer, int &client, Player &p,
                    std::queue<Player> &waitingPlayers, std::list<Player> &loginPlayers);

void managedGameCommands(char *buffer, int &sizeBuffer, int &client, Player &p, Player &p2);

#endif
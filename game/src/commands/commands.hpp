#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include "../classes/player/Player.hpp"

void managedCommand(char *buffer, int &sizeBuffer, int &client, Player &p);

#endif
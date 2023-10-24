#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <queue>
#include <sstream>
#include <list>

#include "../classes/player/Player.hpp"
#include "../classes/game/Game.hpp"

void userCommand(int &client, char *buffer, int &sizeBuffer, std::istringstream &stream, Player &p);
void passwordCommand(int &client, char *buffer, int &sizeBuffer, std::list<Player> loginPlayers, std::istringstream &stream, Player &p);
void signupCommand(int &client, char *buffer, int &sizeBuffer, std::list<Player> loginPlayers, std::istringstream &stream, Player &p);
void helpCommand(char *buffer, int &sizeBuffer, int &client);

void managedCommand(char *buffer, int &sizeBuffer, int &client, Player &p,
                    std::queue<Player> &waitingPlayers, std::list<Player> &loginPlayers);

void managedGameCommands(char *buffer, int &sizeBuffer, int &client, Player &p, Player &p2);

#endif
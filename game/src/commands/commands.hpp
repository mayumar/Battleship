#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <queue>
#include <sstream>
#include <list>

#include "../classes/player/Player.hpp"
#include "../classes/game/Game.hpp"

void passwordCommand(int &client, char *buffer, int &sizeBuffer, std::list<Player> &players, std::istringstream &stream, Player &p);
void passwordCommand(int &client, char *buffer, int &sizeBuffer, std::list<Player> &layers, std::istringstream &stream, Player &p);
void signupCommand(int &client, char *buffer, int &sizeBuffer, std::list<Player> &players, std::istringstream &stream, Player &p);
void helpCommand(char *buffer, int &sizeBuffer, int &client);

void managedCommand(char *buffer, int &sizeBuffer, int &client, Player &p,
                    std::list<Player> &players);

void managedGameCommands(char *buffer, int &sizeBuffer, int &client, Game &game, std::list<Player> &players, std::queue<Player> &waitingPlayers, std::list<Game> &games, Player &p, Player &p2);

#endif
#ifndef SERVER_HPP
#define SERVER_HPP

#include <arpa/inet.h>
#include <list>
#include <queue>
#include "../classes/game/Game.hpp"

#define MSG_SIZE 250
#define MAX_CLIENTS 30
#define PORT 2065

void exitClient(int socket, fd_set * readfds, int &numClients, int clientsArray[], std::list<Game> &games, std::list<Player> &players, std::queue<Player> &waitingPlayers);
void manager(int signum);
void gameOver(int &sizeBuffer, Player &p, std::list<Player> &players, std::list<Game> &games);
void setServer();

#endif
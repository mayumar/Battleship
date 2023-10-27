#ifndef SERVER_HPP
#define SERVER_HPP

#include <arpa/inet.h>
#include <list>
#include "../classes/game/Game.hpp"

void exitClient(int socket, fd_set * readfds, int &numClients, int clientsArray[], Game &game, std::list<Player> &players);
void manager(int signum);
void setServer();

#endif
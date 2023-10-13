#ifndef SERVER_HPP
#define SERVER_HPP

#include <arpa/inet.h>

void setServer();
void manager(int signum);
void exitClient(int socket, fd_set * readfds, int * numClients, int clientsArray[]);

#endif
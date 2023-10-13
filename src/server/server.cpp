#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

#include "server.hpp"

#define MSG_SIZE 250
#define MAX_CLIENTS 50

void exitClient(int socket, fd_set * readfds, int &numClients, int clientsArray[]){
    char buffer[250];
    int j;

    close(socket);
    FD_CLR(socket, readfds);

    for(j = 0; j < numClients; j++){
        if(clientsArray[j] == socket)
            break;
    }

    for(; j < numClients; j++)
        clientsArray[j] = clientsArray[j+1];
    
    numClients--;

    bzero(buffer, sizeof(buffer));
    sprintf(buffer, "Desconexion del cliente <%d>", socket);

    for(j = 0; j < numClients; j++){
        if(clientsArray[j] != socket)
            send(clientsArray[j], buffer, sizeof(buffer), 0);
    }
}

void manager(int signum){
    std::cout << std::endl << "Se ha recibido la señal siginit" << std::endl;
    signal(SIGINT, manager);

    //Implementar lo que se desee realizar cuando ocurra la excepción de ctrl+c en el servidor
}

void setServer(){
    int sd, newSd;
    struct sockaddr_in socnkName, from;
    char buffer[MSG_SIZE];

    socklen_t fromLen;
    fd_set readfs, auxfds;

    int exitSelect;
    int clientsArray[MAX_CLIENTS];
    int numClients = 0;

    int i, j, k;

    int received;
    char id[MSG_SIZE];

    int on, ret;
}
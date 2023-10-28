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
#include <queue>
#include <list>

#include "server.hpp"
#include "../aux/aux.hpp"
#include "../commands/commands.hpp"
#include "../classes/game/Game.hpp"

void exitClient(int socket, fd_set * readfds, int &numClients, int clientsArray[], 
                std::list<Game> &games, std::list<Player> &players, std::queue<Player> &waitingPlayers){
    char buffer[MSG_SIZE];
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
    strcpy(buffer, "+Ok. Tu oponente ha terminado la partida.\n");

    auto itGame = findInList(games, searchPlayer(players, socket));    

    removePlayerFromList(players, socket);
    
    if(isInQueue(waitingPlayers, socket))
        removeFromQueue(waitingPlayers, socket);

    if(itGame->getP1().getSocket() == socket){

        auto p = searchPlayer(players, itGame->getP2().getSocket());
        send(p.getSocket(), buffer, sizeof(buffer), 0);
        auto itPlayer = findInList(players, p);
        itPlayer->setIsPlaying(false);

    }else if(itGame->getP2().getSocket() == socket){
        auto p = searchPlayer(players, itGame->getP1().getSocket());
        send(p.getSocket(), buffer, sizeof(buffer), 0);
        auto itPlayer = findInList(players, p);
        itPlayer->setIsPlaying(false);
    }

    games.erase(itGame);

}

void manager(int signum){
    std::cout << std::endl << "Saliendo..." << std::endl;
    exit(-1);
    signal(SIGINT, manager);
    //Implementar lo que se desee realizar cuando ocurra la excepción de ctrl+c en el servidor
}

void gameOver(int &sizeBuffer, Player &p, std::list<Player> &players, std::list<Game> &games){
    std::string gameOver;

    auto itGame = findInList(games, p);

    if(itGame->getBoardp1().getshipsAlive() == 0){
        gameOver = ("+Ok. " + itGame->getP2().getUsername() + " ha ganado, número de disparos " +
                    std::to_string(itGame->getP2Shots()) + "\n");

        auto itWinner = findInList(players, itGame->getP2());
        itWinner->setIsPlaying(false);
        auto itLoser = findInList(players, itGame->getP1());
        itLoser->setIsPlaying(false);
        send(itGame->getP1().getSocket(), gameOver.data(), sizeBuffer, 0);
        send(itGame->getP2().getSocket(), gameOver.data(), sizeBuffer, 0);
        games.erase(itGame);
    } else if(itGame->getBoardp2().getshipsAlive() == 0){
        gameOver = ("+Ok. " + itGame->getP1().getUsername() + " ha ganado, número de disparos " +
                    std::to_string(itGame->getP1Shots()) + "\n");

        auto itWinner = findInList(players, itGame->getP1());
        itWinner->setIsPlaying(false);
        auto itLoser = findInList(players, itGame->getP2());
        itLoser->setIsPlaying(false);
        send(itGame->getP1().getSocket(), gameOver.data(), sizeBuffer, 0);
        send(itGame->getP2().getSocket(), gameOver.data(), sizeBuffer, 0);
        games.erase(itGame);
    }
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
    
    Player p, p2;
    std::list<Game> games;
    std::queue<Player> waitingPlayers;
    std::list<Player> players;

    int i, j, k;

    int received;
    char id[MSG_SIZE];

    int on, ret;

    sd = socket(AF_INET, SOCK_STREAM, 0);

    if(sd == -1){
        std::cerr << "Error al crear el socket" << std::endl;
        exit(1);
    }

    on = 1;
    ret = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    socnkName.sin_family = AF_INET;
    socnkName.sin_port = htons(PORT);
    socnkName.sin_addr.s_addr = INADDR_ANY;

    if(bind(sd, (struct sockaddr *)&socnkName, sizeof(socnkName)) == -1){
        std::cerr << "Error al enlazar el socket" << std::endl;
        exit(0);
    }

    fromLen = sizeof(from);
    
    if(listen(sd, 1) == -1){
        std::cerr << "Error al escuchar" << std::endl;
        exit(1);
    }

    std::cout << "Esperando conexiones..." << std::endl;

    FD_ZERO(&readfs);
    FD_ZERO(&auxfds);
    FD_SET(sd, &readfs);
    FD_SET(0, &readfs);

    signal(SIGINT, manager);

    while(true){
        auxfds = readfs;
        exitSelect = select(FD_SETSIZE, &auxfds, NULL, NULL, NULL);

        if(exitSelect > 0){
            for(i = 0; i < FD_SETSIZE; i++){
                if(FD_ISSET(i, &auxfds)){
                    if(i == sd){
                        if((newSd = accept(sd, (struct sockaddr *)&from, &fromLen)) != -1){
                            if(numClients < MAX_CLIENTS){
                                clientsArray[numClients] = newSd;
                                numClients++;
                                FD_SET(newSd, &readfs);
                                strcpy(buffer, "+OK. Usuario conectado\n");
                                send(newSd, buffer, sizeof(buffer), 0);

                                std::cout << "Nuevo jugador conectado <" << newSd << ">" << std::endl;

                            } else {
                                bzero(buffer, sizeof(buffer));
                                strcpy(buffer, "Demasiados clientes conectados\n");
                                send(newSd, buffer, sizeof(buffer), 0);
                                close(newSd);
                            }
                        } else std::cerr << "Error al aceptar peticiones" << std::endl;
                        
                    } else if (i == 0) {
                        bzero(buffer, sizeof(buffer));
                        fgets(buffer, sizeof(buffer), stdin);

                        if(strcmp(buffer, "SALIR\n") == 0){
                            for(j = 0; j < numClients; j++){
                                bzero(buffer, sizeof(buffer));
                                strcpy(buffer, "Saliendo del chat\n");
                                send(clientsArray[j], buffer, sizeof(buffer), 0);
                                close(clientsArray[j]);
                                FD_CLR(clientsArray[j], &readfs);
                            }
                            
                            close(sd);
                            exit(-1);
                        }
                        //Mensajes que se quieran mandar a los clientes (implementar)
                    } else {
                        //Server recibe datos
                        bzero(buffer, sizeof(buffer));
                        received = recv(i, buffer, sizeof(buffer), 0);

                        if(received > 0){
                            if(strcmp(buffer, "SALIR\n") != 0){
                                int sizeBuffer = sizeof(buffer);
                                p = searchPlayer(players, i);
                                auto itGame = findInList(games, p);

                                if(!p.isLogin() && !p.isPlaying()){

                                    managedCommand(buffer, sizeBuffer, i, p, players);

                                } else if(strcmp(buffer, "INICIAR-PARTIDA\n") == 0 && !p.isPlaying()) {
                                    
                                    setGame(buffer, sizeBuffer, players, waitingPlayers, games, p, p2);
                                    
                                } else if(p.isPlaying()) {

                                    if(itGame->getTurn() == 1){
                                        strcpy(buffer, "+Ok. Turno de partida.\n");
                                        send(itGame->getP1().getSocket(), buffer, sizeBuffer, 0);
                                        if(itGame->getP2().getSocket() == i){
                                            strcpy(buffer, "-Err. Debe esperar su turno.\n");
                                            send(i, buffer, sizeBuffer, 0);
                                        }else{
                                            managedGameCommands(buffer, sizeBuffer, i, *itGame);
                                        }
                                    }else if(itGame->getTurn() == 2){
                                        strcpy(buffer, "+Ok. Turno de partida.\n");
                                        send(itGame->getP2().getSocket(), buffer, sizeBuffer, 0);
                                        if(itGame->getP1().getSocket() == i){
                                            strcpy(buffer, "-Err. Debe esperar su turno.\n");
                                            send(i, buffer, sizeBuffer, 0);
                                        }else{
                                            managedGameCommands(buffer, sizeBuffer, i, *itGame);
                                        }
                                    }

                                    gameOver(sizeBuffer, p, players, games);
                                
                                }
                                
                            } else exitClient(i, &readfs, numClients, clientsArray, games, players, waitingPlayers);
                        } else if(received == 0){
                            std::cout << "El jugador <" << i << "> ha salido del juego" << std::endl;
                            exitClient(i, &readfs, numClients, clientsArray, games, players, waitingPlayers);
                        }
                    }      
                }
            }
        }
    }

    close(sd);
}
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

#define MSG_SIZE 600
#define MAX_CLIENTS 30

void exitClient(int socket, fd_set * readfds, int &numClients, int clientsArray[]){
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
    sprintf(buffer, "Desconexion del cliente <%d>", socket);

    for(j = 0; j < numClients; j++){
        if(clientsArray[j] != socket)
            send(clientsArray[j], buffer, sizeof(buffer), 0);
    }
}

void manager(int signum){
    std::cout << std::endl << "Se ha recibido la señal siginit" << std::endl;
    exit(-1);
    signal(SIGINT, manager);
    //Implementar lo que se desee realizar cuando ocurra la excepción de ctrl+c en el servidor
}

void setServer(){
    int sd, newSd;
    struct sockaddr_in socnkName, from;
    char buffer[MSG_SIZE];
    const int PORT = 2000;

    socklen_t fromLen;
    fd_set readfs, auxfds;

    int exitSelect;
    int clientsArray[MAX_CLIENTS];
    int numClients = 0;
    
    Player p, p2;
    Game game;
    std::queue<Player> waitingPlayers;
    std::list<Player> loginPlayers;

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
                                
                                //NECESARIO????
                                for(j = 0; j < (numClients-1); j++){
                                    bzero(buffer, sizeof(buffer));
                                    sprintf(buffer, "Nuevo cliente conectado <%d>", newSd);
                                    send(clientsArray[j], buffer, sizeof(buffer), 0);
                                }

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
                            if(strcmp(buffer, "SALIR") != 0){
                                int sizeBuffer = sizeof(buffer);
                                

                                if(!p.isLogin() && !p.isPlaying()){

                                    managedCommand(buffer, sizeBuffer, i, p, waitingPlayers, loginPlayers);

                                }else if(strcmp(buffer, "INICIAR-PARTIDA\n") == 0 && !p.isPlaying()) {
                                    
                                    p = searchPlayer(loginPlayers, i);
                                    if(waitingPlayers.empty()){

                                        strcpy(buffer, "+Ok. Esperando jugadores\n");
                                        waitingPlayers.push(p);
                                        send(p.getSocket(), buffer, sizeBuffer, 0);

                                    } else {

                                        p2 = waitingPlayers.front();
                                        waitingPlayers.pop();
                                        strcpy(buffer, "+Ok. Empieza la partida\n");
                                        send(p.getSocket(), buffer, sizeBuffer, 0);
                                        send(p2.getSocket(), buffer, sizeBuffer, 0);
                                        p.setIsPlaying(true);
                                        p2.setIsPlaying(true);
                                        game.setP1(p2);
                                        game.setP2(p);
                                        game.createGame(sizeBuffer);

                                    }

                                    p = Player();
                                    
                                } else if(searchPlayer(loginPlayers, i).isPlaying()) {

                                    if(game.getTurn() == 1){
                                        if(game.getP2().getSocket() == i){
                                            strcpy(buffer, "-Err. Debe esperar su turno\n");
                                            send(i, buffer, sizeBuffer, 0);
                                        }else{
                                            managedGameCommands(buffer, sizeBuffer, i, game);
                                        }
                                    }else if(game.getTurn() == 2){
                                        if(game.getP1().getSocket() == i){
                                            strcpy(buffer, "-Err. Debe esperar su turno\n");
                                            send(i, buffer, sizeBuffer, 0);
                                        }else{
                                            managedGameCommands(buffer, sizeBuffer, i, game);
                                        }
                                    }

                                    std::string gameOver;

                                    if(game.getBoardp1().getshipsAlive() == 0){
                                        gameOver = ("+Ok. " + game.getP2().getUsername() + " ha ganado\n");
                                    }else if(game.getBoardp2().getshipsAlive() == 0){
                                        gameOver = ("+Ok. " + game.getP1().getUsername() + " ha ganado\n");
                                    }

                                    send(game.getP1().getSocket(), gameOver.data(), sizeBuffer, 0);
                                    send(game.getP2().getSocket(), gameOver.data(), sizeBuffer, 0);
                                    
                                }
                                
                            } else exitClient(i, &readfs, numClients, clientsArray);
                        } else if(received == 0){
                            std::cout << "El socket <" << i << "> se ha cerrado con CTRL+C" << std::endl;
                            exitClient(i, &readfs, numClients, clientsArray);
                        }
                    }      
                }
            }
        }
    }

    close(sd);
}
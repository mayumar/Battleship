#include <iostream>
#include <string.h>
#include <sstream>
#include <map>

#include "commands.hpp"
#include "../aux/aux.hpp"
#include "../auth/auth.hpp"
#include "../server/server.hpp"
#include "../classes/player/Player.hpp"

void managedCommand(char *buffer, int &sizeBuffer, int &client, Player &p,
                    std::queue<Player> &players, std::list<Player> &loginPlayers){
    std::string stringBuffer = buffer;
    cleanString(stringBuffer);

    std::map<std::string, int> coordsMap = {
        {"A", 0},
        {"B", 1},
        {"C", 2},
        {"D", 3},
        {"E", 4},
        {"F", 5},
        {"G", 6},
        {"H", 7},
        {"I", 8},
        {"J", 9},
    };

    std::istringstream stream(stringBuffer);
    std::string command;
    stream >> command;
    
    bzero(buffer, sizeBuffer);

    if(command == "USUARIO"){
        std::string username;
        stream >> username;

        loginUsername(username) ? strcpy(buffer, "+Ok. Usuario correcto.\n") 
                                : strcpy(buffer, "-Err. Usuario incorrecto.\n");

        p.setUsername(username);
        send(client, buffer, sizeBuffer, 0);
        return;
    }

    if(command == "PASSWORD"){
        if(p.getUsername() == ""){
            strcpy(buffer, "-Err. No se ha introducido el nombre de usuario.\n");
            return;
        }

        std::string password;
        stream >> password;


        loginPass(password) ? strcpy(buffer, "+Ok. Usuario valido.\n") 
                            : strcpy(buffer, "-Err. Error en la validacion.\n");
        
        p.setPassword(password);
        p.setIsLogin(true);
        p.setSocket(client);
        addLoginPlayer(loginPlayers, p);
        send(client, buffer, sizeBuffer, 0);
        return;
    }

    if(command == "REGISTRO"){
        std::string option, username, password;
        stream >> option >> username >> option >> password;

        p = signup(username, password, client);

        if(p.getUsername() == "" || p.getPassword() == "")
            strcpy(buffer, "-Err. El jugador ya ha sido registardo.\n");
        else
            strcpy(buffer, "+Ok. Jugador registrado con exito.\n");

        p.setIsLogin(true);
        p.setSocket(client);
        addLoginPlayer(loginPlayers, p);
        send(client, buffer, sizeBuffer, 0);
        return;
    }

    if(command == "INICIAR-PARTIDA"){
        strcpy(buffer, "-Err. El usuario no esta logueado.\n"); //TODO
        send(client, buffer, sizeBuffer, 0);
    }

    if(command == "DISPARO"){
        std::string word, numSTR;
        stream >> word >> numSTR;
        int num = std::stoi(numSTR);

        std::vector<int> realCoords = {num, coordsMap[word]}; //VECTOR CON LAS COORDENADAS
                                                              //Va al revés por culpa de C++

        sprintf(buffer, "+Ok. Disparo en: %s, %d.\n", word.data(), num);
        send(client, buffer, sizeBuffer, 0);
        return;
    }
    
    if(command == "HELP"){
        std::string helpMessage = "USUARIO <usuario>\n"
                                  "PASSWORD <password>\n"
                                  "REGISTRO -u <usuario> -p <password>\n"
                                  "INICIAR-PARTIDA\n"
                                  "DISPARO <letra> <numero>\n"
                                  "SALIR\n";

        strcpy(buffer, helpMessage.data());
        send(client, buffer, sizeBuffer, 0);
        return;
    }
}

void managedGameCommands(char *buffer, int &sizeBuffer, int &client, Player &p, Player &p2){
    

}

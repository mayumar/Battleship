#include <iostream>
#include <string.h>
#include <sstream>
#include <map>

#include "commands.hpp"
#include "../aux/aux.hpp"
#include "../auth/auth.hpp"
#include "../server/server.hpp"
#include "../classes/player/Player.hpp"

void userCommand(int &client, char *buffer, int &sizeBuffer, std::list<Player> &players,
                 std::istringstream &stream, Player &p) {
    std::string username;
    stream >> username;

    loginUsername(username) ? strcpy(buffer, "+Ok. Usuario correcto.\n") 
                            : strcpy(buffer, "-Err. Usuario incorrecto.\n");

    p.setUsername(username);
    p.setSocket(client);
    players.push_back(p);
    send(client, buffer, sizeBuffer, 0);
    return;
}

void passwordCommand(int &client, char *buffer, int &sizeBuffer, std::list<Player> &players, 
                     std::istringstream &stream, Player &p) {
    if(p.getUsername() == ""){
        strcpy(buffer, "-Err. No se ha introducido el nombre de usuario.\n");
        return;
    }

    std::string password;
    stream >> password;

    loginPass(password) ? strcpy(buffer, "+Ok. Usuario valido.\n") 
                        : strcpy(buffer, "-Err. Error en la validacion.\n");
    
    
    auto it = findInList(players, p);
    it->setPassword(password);
    it->setIsLogin(true);

    send(client, buffer, sizeBuffer, 0);
    return;
}

void signupCommand(int &client, char *buffer, int &sizeBuffer, std::list<Player> &players, 
                   std::istringstream &stream, Player &p) {
    std::string option, username, password;
    stream >> option >> username >> option >> password;

    p = signup(username, password, client);

    if(p.getUsername() == "" || p.getPassword() == "")
        strcpy(buffer, "-Err. El jugador ya ha sido registardo.\n");
    else
        strcpy(buffer, "+Ok. Jugador registrado con exito.\n");

    p.setIsLogin(true);
    p.setSocket(client);
    players.push_back(p);
    send(client, buffer, sizeBuffer, 0);
    return;
}

void helpCommand(char *buffer, int &sizeBuffer, int &client) {
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

void managedCommand(char *buffer, int &sizeBuffer, int &client, Player &p,
                    std::list<Player> &players){
    std::string stringBuffer = buffer;
    cleanString(stringBuffer);

    std::istringstream stream(stringBuffer);
    std::string command;
    stream >> command;
    
    bzero(buffer, sizeBuffer);

    if(command == "USUARIO")
        userCommand(client, buffer, sizeBuffer, players, stream, p);
    else if(command == "PASSWORD") 
        passwordCommand(client, buffer, sizeBuffer, players, stream, p);
    else if(command == "REGISTRO") 
        signupCommand(client, buffer, sizeBuffer, players, stream, p);
    else if(command == "HELP")
        helpCommand(buffer, sizeBuffer, client);
    else if(command == "INICIAR-PARTIDA") {
        strcpy(buffer, "-Err. El usuario no esta logueado.\n");
        send(client, buffer, sizeBuffer, 0);
    } else {
        strcpy(buffer, "-Err. Comando incorrecto.\n");
        send(client, buffer, sizeBuffer, 0);
    }
}

void managedGameCommands(char *buffer, int &sizeBuffer, int &client, Game &game){
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

    if(command == "DISPARO"){
        std::string word, numSTR;
        stream >> word >> numSTR;
        int num = std::stoi(numSTR);

        std::vector<int> realCoords = {num-1, coordsMap[word]}; //VECTOR CON LAS COORDENADAS
                                                                //Va al revés por culpa de C++

        sprintf(buffer, "+Ok. Disparo en: %s, %d.\n", word.data(), num);

        if(game.getP1().getSocket() == client)
            send(game.getP2().getSocket(), buffer, sizeBuffer, 0);
        else if(game.getP2().getSocket() == client)
            send(game.getP1().getSocket(), buffer, sizeBuffer, 0);

        game.shot(realCoords, (word + "," + std::to_string(num)), sizeBuffer);
        return;
    }    
}

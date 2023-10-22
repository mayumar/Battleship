#include <iostream>
#include <string.h>
#include <sstream>

#include "commands.hpp"
#include "../aux/aux.hpp"
#include "../auth/auth.hpp"
#include "../server/server.hpp"
#include "../classes/player/Player.hpp"

void managedCommand(char *buffer, int &sizeBuffer, int &client, Player &p){
    std::string command;
    std::string stringBuffer = buffer;
    cleanString(stringBuffer);
    std::istringstream stream(stringBuffer);

    stream >> command;

    if(command == "USUARIO"){
        std::string username;
        stream >> username;

        bzero(buffer, sizeBuffer);

        loginUsername(username) ? strcpy(buffer, "+Ok. Usuario correcto.\n") : strcpy(buffer, "-Err. Usuario incorrecto.\n");

        p.setUsername(username);
        return;
    }

    if(command == "PASSWORD"){
        if(p.getUsername() == ""){
            strcpy(buffer, "-Err. No se ha introducido el nombre de usuario.\n");
            return;
        }

        std::string password;
        stream >> password;

        bzero(buffer, sizeBuffer);

        loginPass(password) ? strcpy(buffer, "+Ok. Usuario valido.\n") : strcpy(buffer, "-Err. Error en la validacion.\n");
        
        p.setPassword(password);
        p.setIsLogin(true);
        return;
    }

    if(command == "REGISTRO"){
        std::string option, username, password;
        stream >> option >> username >> option >> password;

        bzero(buffer, sizeBuffer);

        p = signup(username, password);

        if(p.getUsername() == "" || p.getPassword() == "")
            strcpy(buffer, "-Err. El jugador ya ha sido registardo.\n");
        else
            strcpy(buffer, "+Ok. Jugador registrado con exito.\n");

        p.setIsLogin(true);
        return;
    }

    if(command == "HELP"){
        bzero(buffer, sizeBuffer);
        
        const char* helpMessage = "USUARIO <usuario>\nPASSWORD <password>\nREGISTRO -u <usuario> -p <password>\nINICIAR-PARTIDA\nDISPARO <letra> <numero>\nSALIR\n";

        strcpy(buffer, helpMessage);
        return;
    }
}
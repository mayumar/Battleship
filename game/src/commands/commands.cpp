#include <iostream>
#include <string.h>

#include "commands.hpp"
#include "../aux/aux.hpp"
#include "../auth/auth.hpp"
#include "../server/server.hpp"
#include "../classes/player/Player.hpp"

void managedCommand(char *buffer, int &sizeBuffer, int &client, Player &p){
    if(strstr(buffer, "USUARIO")){
        std::string username;
        username = strtok(buffer, " ");

        if(!username.empty())
            username = strtok(nullptr, " ");

        username = cleanString(username);

        bzero(buffer, sizeBuffer);

        loginUsername(username) ? strcpy(buffer, "+Ok. Usuario correcto.\n") : strcpy(buffer, "-Err. Usuario incorrecto.\n");

        p.setUsername(username);
        
        send(client, buffer, sizeBuffer, 0);//Y SI SEPARO ESTO?????
        return;
    }

    if(strstr(buffer, "PASSWORD")){
        std::string password;
        password = strtok(buffer, " ");

        if(!password.empty())
            password = strtok(nullptr, " ");

        password = cleanString(password);

        bzero(buffer, sizeBuffer);

        loginPass(password) ? strcpy(buffer, "+Ok. Usuario valido.\n") : strcpy(buffer, "-Err. Error en la validacion.\n");
        
        p.setPassword(password);

        send(client, buffer, sizeBuffer, 0);//Y SI SEPARO ESTO?????
        return;
    }

    if(strstr(buffer, "REGISTRO")){
        std::string command, username, password;
        command = strtok(buffer, " ");

        if(!(command = strtok(nullptr, " ")).empty()){
            if(command == "-u"){
                command = strtok(nullptr, " ");
                if(!command.empty())
                    username = command;
            }

            command = strtok(nullptr, " ");
            
            if(command == "-p"){
                command = strtok(nullptr, " ");
                if(!command.empty())
                    password = command;
            }
        }

        username = cleanString(username);
        password = cleanString(password);

        bzero(buffer, sizeBuffer);

        p = signup(username, password);

        if(p.getUsername() == "" || p.getPassword() == "")
            strcpy(buffer, "-Err. El jugador ya ha sido registardo.\n");
        else
            strcpy(buffer, "+Ok. Jugador registrado con exito.\n");
        
        send(client, buffer, sizeBuffer, 0); //Y SI SEPARO ESTO?????
        return;
    }
}
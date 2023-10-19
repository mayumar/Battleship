#include <iostream>
#include <string.h>

#include "commands.hpp"
#include "../aux/aux.hpp"
#include "../auth/auth.hpp"
#include "../server/server.hpp"

void managedCommand(char *buffer, int &sizeBuffer, int &client){
    if(strstr(buffer, "USUARIO")){
        std::string user;
        user = strtok(buffer, " ");

        if(!user.empty())
            user = strtok(nullptr, " ");

        user = cleanString(user);

        bzero(buffer, sizeBuffer);

        if(loginUser(user))
            strcpy(buffer, "+Ok. Usuario correcto.\n");
        else
            strcpy(buffer, "-Err. Usuario incorrecto.\n");
        
        send(client, buffer, sizeBuffer, 0);
        return;
    }

    if(strstr(buffer, "PASSWORD")){
        std::string password;
        password = strtok(buffer, " ");

        if(!password.empty())
            password = strtok(nullptr, " ");

        password = cleanString(password);

        bzero(buffer, sizeBuffer);

        if(loginPass(password))
            strcpy(buffer, "+Ok. Usuario valido.\n");
        else
            strcpy(buffer, "-Err. Error en la validacion.\n");
        
        send(client, buffer, sizeBuffer, 0);
        return;
    }
}
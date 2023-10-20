#include <iostream>
#include <fstream>

#include "auth.hpp"
#include "../classes/player/Player.hpp"

bool loginUsername(std::string user){
    std::ifstream file("../src/files/users.txt");

    if(!file){
        std::cerr << "Error al abrir el fichero" << std::endl;
        return false;
    }

    std::string line, delim = ";";

    while(std::getline(file, line)){
        size_t pos = line.find(delim);

        if(pos == std::string::npos){
            file.close();
            return false;
        }

        std::string userBD = line.substr(0, pos);

        if(userBD == user){
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

bool loginPass(std::string password){
    std::ifstream file("../src/files/users.txt");

    if(!file){
        std::cerr << "Error al abrir el fichero" << std::endl;
        return false;
    }

    std::string line, delim = ";";

    while(std::getline(file, line)){
        size_t pos = line.find(delim);

        if(pos == std::string::npos){
            file.close();
            return false;
        }

        std::string passwordDB = line.substr(pos+1);

        if(passwordDB == password){
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

Player signup(std::string username, std::string password){
    if(loginUsername(username) && loginPass(password))
        return Player();

    std::ofstream file("../src/files/users.txt", std::ios::app);

    if(!file){
        std::cerr << "Error al abrir el fichero" << std::endl;
        return Player();
    }

    file << username << ";" << password << std::endl;
    
    file.close();

    Player p = Player(username, password);
    return p;
}
#include <iostream>
#include <fstream>

#include "auth.hpp"

bool loginUser(std::string user){
    std::ifstream file("../src/files/users.txt");

    if(!file){
        std::cerr << "Error al abrir el fichero" << std::endl;
        return false;
    }

    std::string line, delim = ";";

    while(std::getline(file, line)){
        size_t pos = line.find(delim);

        if(pos == std::string::npos)
            return false;

        std::string userBD = line.substr(0, pos);

        if(userBD == user)
            return true;
    }

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

        if(pos == std::string::npos)
            return false;

        std::string passwordDB = line.substr(pos+1);

        if(passwordDB == password)
            return true;
    }

    return false;
}
#include <iostream>
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sstream>

#include "client.hpp"

void parseBoard(std::string &table, std::vector<std::vector<std::string>> &board) {
    std::vector<std::string> row;
    std::string elem;

    for (char c : table) {
        elem = std::string(1, c);
        if (c == ';') {
            board.push_back(row);
            row.clear();
        } else {
            row.push_back(elem);
        }
    }
}

std::string showBoard(std::vector<std::vector<std::string>> &board) {
    std::string out = "";

    out = "   │ A B C D E F G H I J │\n";
    out += "───┼─────────────────────┼─\n";

    for(int i = 0; i < board.size(); i++){

        if(i != 9){
            out += (" " + std::to_string(i+1) + " │ ");
        }else{
            out += (std::to_string(i+1) + " │ ");
        }

        for(int j = 0; j < board[i].size(); j++){
            std::string point = board[j][i];
            out += (point + " ");
        }

        out += "│\n";
    }

    out += "───┼─────────────────────┼─\n";

    return out;
}

int main(){
    int sd;
    struct sockaddr_in sockName;
    char buffer[250];
    socklen_t sockNameLen;
    fd_set readfds, auxfds;
    int exitSelect;
    bool end = false;

    sd = socket(AF_INET, SOCK_STREAM, 0);

    if(sd == -1){
        std::cerr << "No se puede abrir el socket del cliente" << std::endl;
        exit(-1);
    }

    sockName.sin_family = AF_INET;
	sockName.sin_port = htons(2000);
	sockName.sin_addr.s_addr =  inet_addr("127.0.0.1"); //127.0.0.1

	/* ------------------------------------------------------------------
		Se solicita la conexión con el servidor
	-------------------------------------------------------------------*/
	sockNameLen = sizeof(sockName);
	
	if(connect(sd, (struct sockaddr *)&sockName, sockNameLen) == -1){
		perror ("Error de conexión");
		exit(1);
	}

    FD_ZERO(&auxfds);
    FD_ZERO(&readfds);

    FD_SET(0, &readfds);
    FD_SET(sd, &readfds);

    do{
        auxfds = readfds;
        exitSelect = select(sd+1, &auxfds, nullptr, nullptr, nullptr);

        if(FD_ISSET(sd, &auxfds)){
            bzero(buffer, sizeof(buffer));
            recv(sd, buffer, sizeof(buffer), 0); //RECIBO DE DATOS

            std::string stringBuffer = buffer;

            std::string subcadena = "+Ok. Empezamos partida.";
            size_t pos;

            if((pos = stringBuffer.find(subcadena)) != std::string::npos) {
                std::string formatTable = stringBuffer.substr(pos + subcadena.length());
                std::vector<std::vector<std::string>> board;
                parseBoard(formatTable, board);
                stringBuffer = showBoard(board);
            }
            
            std::cout << std::endl << stringBuffer << std::endl;

            if(strcmp(buffer, "Demasiados clientes conectados\n") == 0 || strcmp(buffer,"Desconexión servidor\n") == 0)
                end = true;
            
            if(strcmp(buffer,"Desconexión servidor\n") == 0)
                end = true;
        } else {
            if(FD_ISSET(0, &auxfds)){
                bzero(buffer, sizeof(buffer));
                fgets(buffer, sizeof(buffer), stdin);

                if(strcmp(buffer, "SALIR\n") == 0)
                    end = true;
                
                send(sd, buffer, sizeof(buffer), 0);
            }
        }
    }while(!end);

    // close(sd);
    return 0;
}

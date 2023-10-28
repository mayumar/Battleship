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
#include "client_game.hpp"
#include "board_manager.hpp"

int main(){
    int sd;
    struct sockaddr_in sockName;
    char buffer[250];
    socklen_t sockNameLen;
    fd_set readfds, auxfds;
    int exitSelect;
    bool end = false;

    std::vector<std::vector<std::string>> my_board, board, p2Board;
    board = std::vector<std::vector<std::string>>(10, std::vector<std::string>(10, "-"));

    sd = socket(AF_INET, SOCK_STREAM, 0);

    if(sd == -1){
        std::cerr << "No se puede abrir el socket del cliente" << std::endl;
        exit(-1);
    }

    sockName.sin_family = AF_INET;
	sockName.sin_port = htons(PORT);
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
        
            std::string startingString = "+Ok. Empieza la partida.";
            std::string shotString = "+Ok. Disparo en: ";
            size_t pos;

            if((pos = stringBuffer.find(startingString)) != std::string::npos) {

                std::cout << std::endl << startingString << std::endl << std::endl;

                std::cout << "======== MIS BARCOS =======" << std::endl;
                
                std::string formatTable = stringBuffer.substr(pos + startingString.length());
                parseBoard(formatTable, my_board);
                stringBuffer = showBoard(my_board);

            } else if((pos = stringBuffer.find(shotString)) != std::string::npos) {
                std::cout << std::endl << stringBuffer << std::endl << std::endl;
                
                std::cout << "========= OPONENTE ========" << std::endl;

                std::string coords = stringBuffer.substr(pos + shotString.length());
                p2Game(coords, my_board);

                stringBuffer = showBoard(my_board);
            } else {

                manageReponse(stringBuffer, board);
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

    close(sd);
    return 0;
}

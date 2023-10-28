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

int main(){
    int sd;
    struct sockaddr_in sockName;
    char buffer[250];
    socklen_t sockNameLen;
    fd_set readfds, auxfds;
    int exitSelect;
    bool end = false;
    const int PORT = 2065;

    std::vector<std::vector<std::string>> board;
    board = std::vector<std::vector<std::string>>(10, std::vector<std::string>(10, "-"));
    std::vector<int> shot(2);
    
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
            std::string waterString = "+Ok. AGUA: ";
            std::string hittedString = "+Ok. TOCADO: ";
            std::string sinkedString = "+Ok. HUNDIDO: ";
            size_t pos;

            if((pos = stringBuffer.find(startingString)) != std::string::npos) {
                
                std::cout << startingString << std::endl << std::endl;
                std::string formatTable = stringBuffer.substr(pos + startingString.length());
                std::vector<std::vector<std::string>> my_board;
                parseBoard(formatTable, my_board);
                stringBuffer = showBoard(my_board);

            }else if((pos = stringBuffer.find(waterString)) != std::string::npos){
                
                std::cout << stringBuffer << std::endl << std::endl;
                std::string coords = stringBuffer.substr(pos + waterString.length());
                getCoords(coords, shot);

                if(board[shot[1]][shot[0]] == "-")
                    board[shot[1]][shot[0]] = "A";

                stringBuffer = showBoard(board);

            }else if((pos = stringBuffer.find(hittedString)) != std::string::npos){
                
                std::cout << stringBuffer << std::endl << std::endl;
                std::string coords = stringBuffer.substr(pos + hittedString.length());
                getCoords(coords, shot);
                board[shot[1]][shot[0]] = "X";
                stringBuffer = showBoard(board);

            }else if((pos = stringBuffer.find(sinkedString)) != std::string::npos){
                
                std::cout << stringBuffer << std::endl << std::endl;
                std::string coords = stringBuffer.substr(pos + sinkedString.length());
                getCoords(coords, shot);
                board[shot[1]][shot[0]] = "X";
                sinkShip(board, shot);
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

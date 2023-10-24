#include <iostream>
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

//#include "client.hpp"

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

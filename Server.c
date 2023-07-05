// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 7117
int main(int argc, char const* argv[]) {
    int server_fd, conn_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    //char* serv_resp = ;
    char serv_resp[10] = {0};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 7117
    if (bind(server_fd, (struct sockaddr *) &address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }


    if ((conn_socket
                 = accept(server_fd, (struct sockaddr *) &address,
                          (socklen_t *) &addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    recv_cmd:
    valread = recv(conn_socket, buffer, sizeof(buffer),0);

    strcpy(serv_resp, "RECVD");

    printf("RECV: %s\n", buffer);

    send(conn_socket, serv_resp, strlen(serv_resp), 0);

    printf("RESP: %c\n", *serv_resp);


    if ((buffer[0] != 37) && (buffer[1] != 113)) {
        fflush(stdout);
        goto recv_cmd;
    }
    else {

        // closing the connected socket
        close(conn_socket);
        // closing the listening socket
        shutdown(server_fd, SHUT_RDWR);
    }


    return 0;
}

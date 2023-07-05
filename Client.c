// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 7117

int main(int argc, char const* argv[])
{
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char client_cmd[512];
    char buffer[1024] = {0};

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
                "\nInvalid address/ Address not supported \n");
        return -1;
    }

    int done_cmd = 1;


    if ((status
                 = connect(client_fd, (struct sockaddr*)&serv_addr,
                           sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;

    }

    send_cmd:
    // Term commands with '!'
    // End read loop with '%q!'
    printf("> ");
    scanf("%[^!]s", client_cmd);


    send(client_fd, client_cmd, sizeof(client_cmd), 0);
    printf("\nSENT\n");



    valread = recv(client_fd, buffer, sizeof(buffer), 0);

    printf("RESPONSE: %s\n", buffer);

    if ((client_cmd[0] != 37) && (client_cmd[1] != 113)) {
        // (clears the input buffer)
        while ((getchar()) != '\n');
        goto send_cmd;
    }

    // closing the connected socket
    close(client_fd);
    return 0;
}

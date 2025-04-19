
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define BACKLOG 3  // Maximum number of pending connections

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Setting up the address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding the socket to the specified port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listening for incoming connections
    if (listen(server_fd, BACKLOG) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d
", PORT);

    while (1) {
        // Accepting a connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
            perror("Accept failed");
            continue; // Continue to accept other connections
        }

        // Reading data from the client
        ssize_t bytes_read = recv(new_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_read < 0) {
            perror("Read failed");
            close(new_socket);
            continue; // Continue to accept other connections
        }
        buffer[bytes_read] = '\0'; // Null terminate the string
        printf("Message from client: %s
", buffer);

        // Sending response to the client
        ssize_t bytes_sent = send(new_socket, response, strlen(response), 0);
        if (bytes_sent < 0) {
            perror("Send failed");
        } else {
            printf("Response sent to client
");
        }

        // Closing the socket
        close(new_socket);
    }

    // Closing the server socket (unreachable in current loop)
    close(server_fd);
    return 0;
}

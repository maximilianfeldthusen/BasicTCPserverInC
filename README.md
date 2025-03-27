
## Documentation

### Basic-TCP-server


This C code implements a simple TCP server that listens for incoming connections on a specified port (8080) and communicates with the clients. Let's break it down step by step:

### Header Files
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
```
- **stdio.h**: For standard input and output functions (like `printf` and `perror`).
- **stdlib.h**: For general utility functions (like `exit`).
- **string.h**: For string manipulation functions (like `strlen`).
- **unistd.h**: For standard symbolic constants and types (like `close`).
- **arpa/inet.h**: For Internet operations (like `htons` and `INADDR_ANY`).
- **sys/types.h** and **sys/socket.h**: For socket programming types and functions.

### Constants
```c
#define PORT 8080
#define BUFFER_SIZE 1024
#define BACKLOG 3  // Maximum number of pending connections
```
- **PORT**: The port number on which the server listens for incoming connections.
- **BUFFER_SIZE**: The size of the buffer used to read data from the client.
- **BACKLOG**: The maximum number of pending connections that can be queued while the server is processing another connection.

### Main Function
```c
int main() {
```
This is the entry point of the program.

### Socket Creation
```c
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
```
- **socket()**: A system call to create a new socket. The parameters specify the address family (IPv4), socket type (TCP), and protocol (0 means use the default protocol).
- If the socket creation fails, it prints an error message and exits.

### Setting Up the Address Structure
```c
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);
```
- **sin_family**: Specifies the address family (IPv4 in this case).
- **sin_addr.s_addr**: Set to `INADDR_ANY` so that the server accepts connections on any of the host's IP addresses.
- **sin_port**: The port number, converted to network byte order using `htons()`.

### Binding the Socket
```c
if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("Bind failed");
    close(server_fd);
    exit(EXIT_FAILURE);
}
```
- **bind()**: Associates the socket with the address specified in `address`. If it fails, it prints an error message, closes the socket, and exits.

### Listening for Connections
```c
if (listen(server_fd, BACKLOG) < 0) {
    perror("Listen failed");
    close(server_fd);
    exit(EXIT_FAILURE);
}
```
- **listen()**: Prepares the socket to accept incoming connections. It takes the backlog parameter, which is the maximum number of queued connections.

### Accepting Connections
```c
printf("Server is listening on port %d
", PORT);

while (1) {
    // Accepting a connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
        perror("Accept failed");
        continue; // Continue to accept other connections
    }
```
- The server enters an infinite loop to continuously accept incoming connections.
- **accept()**: Blocks until a client connects, at which point it accepts the connection and returns a new socket file descriptor for communication with the client.

### Reading Data from the Client
```c
    ssize_t bytes_read = recv(new_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_read < 0) {
        perror("Read failed");
        close(new_socket);
        continue; // Continue to accept other connections
    }
    buffer[bytes_read] = '\0'; // Null terminate the string
    printf("Message from client: %s
", buffer);
```
- **recv()**: Reads data sent by the client into the `buffer`. It returns the number of bytes read.
- If reading fails, it closes the connection with the client and continues to accept new connections.
- The data read from the client is null-terminated for safe string handling.

### Sending a Response to the Client
```c
    ssize_t bytes_sent = send(new_socket, response, strlen(response), 0);
    if (bytes_sent < 0) {
        perror("Send failed");
    } else {
        printf("Response sent to client
");
    }
```
- **send()**: Sends a response back to the client. If it fails, an error message is printed.

### Closing the Socket
```c
    // Closing the socket
    close(new_socket);
}
```
- After handling the client, the server closes the connection socket (`new_socket`) to clean up resources.

### Final Closing of the Server Socket
```c
// Closing the server socket (unreachable in current loop)
close(server_fd);
return 0;
```
- The server socket (`server_fd`) is closed, though in this implementation, it is unreachable because of the infinite loop. In a real application, you would want a mechanism to break out of the loop and clean up resources gracefully.

### Summary
This code sets up a simple TCP server that listens on port 8080, accepts client connections, reads messages from clients, sends a response, and continues to serve new clients in a loop. It includes error handling for socket creation, binding, listening, reading, and sending.





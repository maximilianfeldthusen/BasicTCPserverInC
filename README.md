## Documentation

### Overview:
This code implements a simple TCP server that listens on port 8080. When a client connects, the server reads a message sent by the client, prints it out, and responds with a greeting message. It then closes the connection and waits for the next client.

---

### Breakdown of the Code:

#### 1. **Include Necessary Headers**
```c
#include <stdio.h>      // For printf, perror
#include <stdlib.h>     // For exit, EXIT_FAILURE
#include <string.h>     // For strlen
#include <unistd.h>     // For close
#include <arpa/inet.h>  // For sockaddr_in, inet_addr
#include <sys/types.h>  // Data types
#include <sys/socket.h> // For socket functions
```
These headers provide the functions and constants needed for socket programming, input/output, memory management, etc.

---

#### 2. **Define Constants**
```c
#define PORT 8080
#define BUFFER_SIZE 1024
#define BACKLOG 3  // Number of pending connections queue
```
- `PORT`: The port number the server listens on.
- `BUFFER_SIZE`: Size of the buffer for reading client data.
- `BACKLOG`: Max number of queued connection requests.

---

#### 3. **Main Function and Variable Declarations**
```c
int server_fd, new_socket;
struct sockaddr_in address;
socklen_t addrlen = sizeof(address);
char buffer[BUFFER_SIZE] = {0};
const char *response = "Hello from server";
```
- `server_fd`: Socket file descriptor for the server.
- `new_socket`: Socket file descriptor for each accepted client connection.
- `address`: Structure holding server address info.
- `buffer`: Buffer to store data received from clients.
- `response`: Message sent back to clients.

---

#### 4. **Create a Socket**
```c
if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
}
```
- Creates a TCP socket (`SOCK_STREAM`).
- Checks if socket creation failed.

---

#### 5. **Configure Server Address**
```c
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address
address.sin_port = htons(PORT);       // Convert port to network byte order
```
- `AF_INET`: IPv4 addresses.
- `INADDR_ANY`: Binds to all available interfaces.
- `htons()`: Converts port number to network byte order.

---

#### 6. **Bind Socket to Address**
```c
if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("Bind failed");
    close(server_fd);
    exit(EXIT_FAILURE);
}
```
- Associates the socket with the specified IP address and port.

---

#### 7. **Listen for Incoming Connections**
```c
if (listen(server_fd, BACKLOG) < 0) {
    perror("Listen failed");
    close(server_fd);
    exit(EXIT_FAILURE);
}
printf("Server is listening on port %d
", PORT);
```
- Starts listening for client connection requests.
- `BACKLOG` specifies the queue size for pending connections.

---

#### 8. **Main Loop: Accept and Handle Connections**
```c
while (1) {
    // Accept a new connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
        perror("Accept failed");
        continue; // Skip to next iteration
    }
```
- `accept()` waits for a client to connect.
- On success, `new_socket` is used for communication with that client.

---

#### 9. **Receive Data from Client**
```c
ssize_t bytes_read = recv(new_socket, buffer, BUFFER_SIZE - 1, 0);
if (bytes_read < 0) {
    perror("Read failed");
    close(new_socket);
    continue;
}
buffer[bytes_read] = '\0'; // Null-terminate received data
printf("Message from client: %s
", buffer);
```
- Reads data sent by the client.
- Ensures the buffer is null-terminated to safely print as a string.
- Prints the client's message.

---

#### 10. **Send Response to Client**
```c
ssize_t bytes_sent = send(new_socket, response, strlen(response), 0);
if (bytes_sent < 0) {
    perror("Send failed");
} else {
    printf("Response sent to client
");
}
```
- Sends a greeting message back to the client.
- Checks for errors in sending.

---

#### 11. **Close Client Connection**
```c
close(new_socket);
```
- Closes the client socket.
- The server then loops back to accept another connection.

---

#### 12. **Cleanup (Unreachable in Current Loop)**
```c
close(server_fd);
return 0;
```
- Closes the server socket when the server terminates (not reachable in this infinite loop).

---

### Summary:
- The server sets up a TCP socket, binds it to port 8080, and begins listening.
- It enters an infinite loop to accept incoming client connections.
- For each client:
  - Reads a message.
  - Prints it.
  - Sends back a greeting.
  - Closes the connection.
- Continues to accept new clients indefinitely.

This is a basic example of socket programming in C, demonstrating server-side TCP communication.

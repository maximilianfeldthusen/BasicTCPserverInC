# BasicTCPserverInC

Simple TCP Server in C

I wrote it for my LinkedIn account 

Constants:
PORT is defined as 8080, which is the port on which the server will listen for incoming connections.
BUFFER_SIZE is set to 1024, which determines the size of the buffer used for reading client messages.

Socket Creation:
The socket() function creates a new socket. If it fails, an error message is printed, and the program exits.

Address Structure Setup:
The sockaddr_in structure is initialized to specify the address family (IPv4), IP address (INADDR_ANY allows the server to accept connections from any IP), and port number (converted to network byte order using htons()).

Binding:
The bind() function associates the socket with the specified address and port. If it fails, an error message is printed, and the server socket is closed.

Listening:
The listen() function allows the server to listen for incoming connections. The second parameter specifies the maximum number of pending connections.

Accepting Connections:
The accept() function waits for a client to connect. Upon a successful connection, it returns a new socket descriptor for communication with the client.

Reading Data:
The server reads data sent by the client using the read() function and stores it in the buffer.

Sending Response:
The server sends a response back to the client using the send() function.

Closing Sockets:
Finally, both the client socket and the server socket are closed to free up resources.

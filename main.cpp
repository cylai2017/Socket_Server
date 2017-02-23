#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    // Instance socket
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    // Set up the socket with IP and port
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));  //Use 0 to fill every character
    server_address.sin_family = AF_INET;  //Use IPv4 address
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");  //Enter the IP address
    server_address.sin_port = htons(1234);  //port
    /* bind() function
     header file : #include <sys/socket.h>
     function definition : int bind(int sockfd, struct sockaddr * my_addr, int addrlen);
     */
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    
    //-------------------------------------------------------------------------------------
    
    //Enter the tap situation, waiting for the client's request.
    listen(server_socket, 100);
    
    //-------------------------------------------------------------------------------------
    
    //Receive the client's request.
    struct sockaddr_in client_address;
    socklen_t client_address_size = sizeof(client_address); // Declare the client address size
    int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size);
    
    //Transfer data to client
    char str[] = "Hello World!";
    write(client_socket, str, sizeof(str));
    
    //Close socket
    close(client_socket);
    close(server_socket);
    
    return 0;
}

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
using namespace std;

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd;
    struct sockaddr_in address, client_addr;
    char buffer[BUFFER_SIZE] = {0};
    socklen_t addr_len = sizeof(client_addr);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    cout << "UDP server is listening on port " << PORT << "..." << endl;

    // Receive message from client
    recvfrom(server_fd, buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&client_addr, &addr_len);
    cout << "Message from client: " << buffer << endl;

    // Send response to client
    const char* response = "Hello from server!";
    sendto(server_fd, response, strlen(response), MSG_CONFIRM, (struct sockaddr*)&client_addr, addr_len);
    cout << "Response sent to client" << endl;

    // Close the socket
    close(server_fd);

    return 0;
}

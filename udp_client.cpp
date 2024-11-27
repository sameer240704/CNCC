#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Creating socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // Send message to server
    const char* message = "Hello from client!";
    sendto(sock, message, strlen(message), MSG_CONFIRM, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    cout << "Message sent to server" << endl;

    // Receive response from server
    socklen_t addr_len = sizeof(serv_addr);
    recvfrom(sock, buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&serv_addr, &addr_len);
    cout << "Message from server: " << buffer << endl;

    // Close the socket
    close(sock);

    return 0;
}

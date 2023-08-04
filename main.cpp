#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void recevieUDP(int);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    //recevieUDP(12345);
    w.show();
    return a.exec();
}

void recevieUDP(int PORT)
{
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    char buffer[1024]; // Increase buffer size

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket." << std::endl;
        return;
    }

    // Bind the socket to the server address and port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error binding socket." << std::endl;
        close(sockfd);
        return;
    }

    std::cout << "UDP server listening on port " << PORT << std::endl;

    // Receive and print incoming data
    while (true) {
        uint totalBytesReceived = 0;
        while (totalBytesReceived < sizeof(buffer) - 1) { // Make sure there's space for the null terminator
            ssize_t numBytes = recvfrom(sockfd, buffer + totalBytesReceived, sizeof(buffer) - 1 - totalBytesReceived, 0,
                                        (struct sockaddr*)&clientAddr, &addrLen);
            if (numBytes < 0) {
                std::cerr << "Error receiving data." << std::endl;
                break;
            } else if (numBytes == 0) {
                std::cout << "Connection closed by the client." << std::endl;
                break;
            } else {
                totalBytesReceived += numBytes;
            }
        }

        buffer[totalBytesReceived] = '\0'; // Null-terminate the received data
        std::cout << "Received: " << buffer << std::endl;
    }

    close(sockfd);
    }

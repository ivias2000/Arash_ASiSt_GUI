#include "udp.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cmath>
#include <typeinfo>

using namespace std;

void udp::run() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket." << std::endl;
        return;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12345);

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error binding socket." << std::endl;
        close(sockfd);
        return;
    }

    std::cout << "UDP server listening on port " << 12345 << std::endl;
    const double pi = 3.14159265358979323846;
    float l__0=0.006;
    float l__1=0.1820;
    float l__3=0.05;
    float l__5=0.1150;
    float l__2=0.07;
    float l__7=0.0342;
    float theta=42*(pi/180);
    float alpha=50*(pi/180);

    while (true) {
        uint totalBytesReceived = 0;

        while (totalBytesReceived < sizeof(buffer) - 1) {
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
                cout << typeid(totalBytesReceived).name() << endl;
            }
        }

        buffer[totalBytesReceived] = '\0';
        std::string received_data(buffer);
        cout << typeid(received_data).name() << endl;

        std::stringstream ss(received_data);
        std::string item;
        std::vector<std::string> data_asly_star;

        while (std::getline(ss, item, '*')) {
            data_asly_star.push_back(item);
        }

        if (!data_asly_star.empty()) {
            float data_q1 = std::stof(data_asly_star[0]);
            float data2_q2 = std::stof(data_asly_star[1]);
            float data3_q3 = std::stof(data_asly_star[2]);
            float data3_timer = std::stof(data_asly_star[3]);
            
            float phi = roundf(float((data_q1) * (pi / 180)) * 10000.0f) / 10000.0f;
            float psi = roundf(float((data2_q2) * (pi / 180)) * 10000.0f) / 10000.0f;
            float d = roundf(float(((-data3_q3)) / 1000) * 10000.0f) / 10000.0f;
            float x = roundf(float((sin(theta) * cos(psi + alpha) * d + cos(theta) * cos(phi) * sin(psi + alpha) * d + sin(theta) * (l__1 + l__3 + l__5))) * 10000.0f) / 10000.0f;
            float y = roundf(static_cast<float>(sin(phi) * sin(psi + alpha) * d) * 10000.0f) / 10000.0f;
            float z = roundf(float((cos(theta) * cos(psi + alpha) * d - cos(phi) * sin(theta) * sin(psi + alpha) * d + cos(theta) * (l__1 + l__3 + l__5))) * 10000.0f) / 10000.0f;

            packet_recieve_handler.setValue(x, y, z, data3_timer);
        }
    }

    close(sockfd);
}

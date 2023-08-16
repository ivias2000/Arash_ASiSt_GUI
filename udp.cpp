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
#include<typeinfo>
using namespace std;
void udp::run() {


    int sockfd;
    //sockaddr_in yany azsakhtar ipv4 estefade mi kone
    struct sockaddr_in serverAddr, clientAddr;
    //socklen_t yek arg baray socket hast
    socklen_t addrLen = sizeof(clientAddr);
    char buffer[1024]; // Increase buffer size

    // Create a UDP socket
    //AF_INET ipv4
    //SOCK_DGRAM  UDP protocol
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    // test etesal ba mofagiat
    if (sockfd < 0) {
        std::cerr << "Error creating socket." << std::endl;
        return;
    }

    // Bind the socket to the server address and port
    serverAddr.sin_family = AF_INET;
    //INADDR_ANY be har shabake mottasel shavad
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    //htons byte shabake
    serverAddr.sin_port = htons(12345);
// etesal namofag
    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error binding socket." << std::endl;
        close(sockfd);
        return;
    }

    std::cout << "UDP server listening on port " << 12345 << std::endl;
    std::vector<std::string> data_asly_star;
    std::string data_baghi;
    //float data2_q2;
    float data3_timer_qabl=0;
    const double pi = 3.14159265358979323846;
    float l__0=0.006;
    float l__1=0.1820;
    //float l__1=0.1760;
    float l__3=0.05;
    float l__5=0.1150;
    float l__2=0.07;
    float l__7=0.0342;
    float theta=42*(pi/180);
    float alpha=50*(pi/180);

    while (true) {
        uint totalBytesReceived = 0;

        while (totalBytesReceived < sizeof(buffer) - 1) { // Make sure there's space for the null terminator

            ssize_t numBytes = recvfrom(sockfd, buffer + totalBytesReceived, sizeof(buffer) - 1 - totalBytesReceived, 0,
                                        (struct sockaddr*)&clientAddr, &addrLen);
            // Aya etesal hast chizi daryaft mishavad
            if (numBytes < 0) {
                std::cerr << "Error receiving data." << std::endl;
                break;
            } else if (numBytes == 0) {
                std::cout << "Connection closed by the client." << std::endl;
                break;
            } else {
                totalBytesReceived += numBytes;
                cout<<typeid(totalBytesReceived).name()<<endl;
            }

        }

        buffer[totalBytesReceived] = '\0'; // Null-terminate the received data!!!!
        //buffer[numBytes] = '\0';
        std::string received_data(buffer);
        cout<<typeid(received_data).name()<<endl;
        // Perform the operations on the received data as in the Python code
        data_baghi = data_baghi + received_data;
        int count=0;

        // dar avardan data hay ma ba asas*#
        for (char c : data_baghi) {
            if (c == '#') {
                count++;
            }
        }

        int i=0;
        for(i=0;i<count;i++){
            size_t n_hashtak = data_baghi.find('#');
            std::string data_asly = data_baghi.substr(0, n_hashtak);
            data_baghi = data_baghi.substr(n_hashtak + 1);
            std::stringstream ss(data_asly);
            std::string item;
            while (std::getline(ss, item, '*')) {
                data_asly_star.push_back(item);
            }

            if (data_asly_star[0] == "") {
                data_asly_star.erase(data_asly_star.begin());
            }


            float data_q1 = std::stof(data_asly_star[0]);
            float data2_q2 = std::stof(data_asly_star[1]);
            float data3_q3 = std::stof(data_asly_star[2]);
            float data3_timer = std::stof(data_asly_star[3]);
            float phi=roundf(float((data_q1)*(pi/180))* 10000.0f) / 10000.0f;
            float psi=roundf(float((data2_q2)*(pi/180))* 10000.0f) / 10000.0f;
            float d=roundf(float(((-data3_q3))/1000)* 10000.0f) / 10000.0f;
            float x=roundf(float((sin(theta) * cos(psi + alpha) * d + cos(theta) * cos(phi) * sin(psi + alpha) * d + sin(theta) * (l__1 + l__3 + l__5)))* 10000.0f) / 10000.0f;
            float y = roundf(static_cast<float>(sin(phi) * sin(psi + alpha) * d) * 10000.0f) / 10000.0f;
            float z=roundf(float((cos(theta) * cos(psi + alpha) * d - cos(phi) * sin(theta) * sin(psi + alpha) * d + cos(theta) * (l__1 + l__3 + l__5)))* 10000.0f) / 10000.0f;

     
            data_asly_star.clear(); // Clear the vector for the next set of data
            packet_recieve_handler.setValue(x,y,z,data3_timer);


        }
    }

    close(sockfd);
}

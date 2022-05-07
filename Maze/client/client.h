#ifndef CLIENT_H
#define CLIENT_H

#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
using namespace std;
class client{
    public:
    int sock=0,valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = { 0 };
    client(){
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("\n Socket creation error \n");
            exit(EXIT_FAILURE);
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        // Convert IPv4 and IPv6 addresses from text to binary
        // form
        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
            <= 0) {
            printf(
                "\nInvalid address/ Address not supported \n");
            exit(EXIT_FAILURE);
        }

        if (connect(sock, (struct sockaddr*)&serv_addr,
                    sizeof(serv_addr))
            < 0) {
            printf("\nConnection Failed \n");
            exit(EXIT_FAILURE);
        }
    }
    string sendrecieve(string lmao){
        for(int i=0;i<1024;i++){
           buffer[i]='\0';
       }
        const char* hello=lmao.c_str();
        send(sock, hello, strlen(hello), 0);

        valread = read(sock, buffer, 1024);

        string s(buffer);
        return s;
    }
};
#endif

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Reagent.h"

#define RESPONSE "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html>Hello, world!</html>"

int main() {

    InitIU(512);

    struct sockaddr_in addr;

    addr.sin_port = htons(80);

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    bind(sock, (struct sockaddr *)&addr, sizeof(addr));

    listen(sock, SOMAXCONN);

    while (1) {

        int User;

        if ((User = accept(sock, NULL, NULL)) < 0) {
            continue;
        }

        Write(User, RESPONSE, strlen(RESPONSE));
        close(User);

    }

    close(sock);
    CloseIU();

    return 0;
}
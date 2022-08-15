#include <iostream>
#ifdef WIN32
#include <windows.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <memory>
#include "../classifier/Classifier.h"
#include "../classifier/Classified.h"
#include "../classifier/distance/Distance.h"
#include "../classifier/distance/EuclideanDistance.h"

int main(int argc, char* argv[]) {

    const int server_port = 5555;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);

    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }

    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
    }

    struct sockaddr_in client_sin;
    //maybe change to unsigned int
    int addr_len = sizeof(client_sin);
    int client_sock = accept(sock,  (struct sockaddr *) &client_sin,  &addr_len);

    if (client_sock < 0) {
        perror("error accepting client");
    }

    char buffer[4096] = {0};
    int expected_data_len = sizeof(buffer);
    int read_bytes = 0;
    Distance* metric = new EuclideanDistance();
    int k = std::stoi(argv[2]);
    std::unique_ptr<Classifier> classifier(new Classifier(k));
    classifier->init(argv[1]);
    while (read_bytes = recv(client_sock, buffer, expected_data_len, 0)) {
        if (read_bytes == 0) {
            // connection is closed
        } else if (read_bytes < 0) {
            // error
        } else {
            std::unique_ptr<Classified> classified_data = std::move(Classified::fromLine(buffer));
            classifier->classify(*classified_data, *metric);
            int sent_bytes = send(client_sock, classified_data->handle().c_str(), classified_data->handle().size(), 0);
            if (sent_bytes < 0) {
                perror("error sending to client");
            }
        }

    }
    close(sock);


    return 0;
}
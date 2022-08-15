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
#include "../classifier/distance/EuclideanDistance.h"

int main(int argc, char* argv[]) {
    const int server_port = 5555;

    // Create a socket for the server
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    // Bind the socket
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);

    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }

    // Listen to a socket, and accept the client
    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
    }

    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock,  (struct sockaddr *) &client_sin,  &addr_len);

    if (client_sock < 0) {
        perror("error accepting client");
    }

    // Communicate with the client
    char buffer[4096] = {0};
    int expected_data_len = sizeof(buffer);
    int read_bytes = 0;

    Distance* metric = new EuclideanDistance();
    std::unique_ptr<Classifier> classifier(new Classifier(std::stoi(argv[2])));
    classifier->initFromFile(argv[1]);

    while (strcmp(buffer, "END") != 0) {
        // Read the unclassified data
        read_bytes = recv(client_sock, buffer, expected_data_len, 0);

        if (read_bytes == 0) {
            break;
        } else if (read_bytes < 0) {
            perror("Error communicating with the server");
        } else {
            // Convert the string to an object, and classify it
            std::unique_ptr<Classified> classified_data = std::move(Classified::fromLine(buffer));
            classifier->classify(*classified_data, *metric);

            // Send the classification to the client
            int sent_bytes = send(client_sock, classified_data->handle().c_str(), classified_data->handle().size(), 0);
            if (sent_bytes < 0) {
                perror("error sending to client");
            }
        }
    }

    delete metric;
    close(sock);

    return 0;
}
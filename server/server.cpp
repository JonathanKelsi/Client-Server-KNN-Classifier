#ifdef WIN32
#include <windows.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#include "../classifier/Classifier.h"
#include "../classifier/distance/EuclideanDistance.h"
#include <unistd.h>
#include <string.h>
#include <memory>
#include <iostream>

int main() {
    // Server Constants
    const int server_port = 5555;
    const int k = 5;

    // Create a socket for the server
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error creating socket");
    }

    // Bind the socket
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);

    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("Error binding socket");
    }

    // Listen for a connection, and accept the client
    if (listen(sock, 5) < 0) {
        perror("Error listening to a socket");
    }

    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock,  (struct sockaddr*)& client_sin,  &addr_len);

    if (client_sock < 0) {
        perror("Error accepting client");
    }

    // Receive the unclassified data from the user
    char buffer[512] = {0};
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(client_sock, buffer, expected_data_len, 0);

    if (read_bytes <= 0) {
        perror("Error communicating with the server");
    }

    // Create a classifier
    std::unique_ptr<Classifier> classifier(new Classifier(k));
    classifier->initFromFile("../server/Data/Classified.csv");

    // Classify the data
    std::unique_ptr<Distance> metric(new EuclideanDistance());
    std::string res = classifier->classify(buffer, *metric);

    // Send the classified data to the client
    int sent_bytes = send(client_sock, res.c_str(), res.size(), 0);
    if (sent_bytes < 0) {
        perror("Error sending classifications to the client");
    }

    close(sock);
    return 0;
}
#include <iostream>
#ifdef WIN32
#include <windows.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <memory>

using namespace std;

int main(int argc, char* argv[]) {
    // Server constants
    const char* ip_address = "127.0.0.1";
    const int port_no = 5555;

    // Creating a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("Error creating socket");
    }

    // Connecting to the server
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);

    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("Error connecting to server");
    }

    // Communication with the server
    std::string line;
    std::ifstream inFile(argv[1]);
    std::ofstream ostream(argv[2]);
    char buffer[4096] = {0};
    int expected_data_len = sizeof(buffer);

    while (std::getline(inFile, line)) {
        // Send the unclassified data to the server
        int sent_bytes = send(sock, line.c_str(), line.size(), 0);

        if (sent_bytes < 0) {
            perror("Error communicating with the server");
        }

        // Receive the classification
        int read_bytes = recv(sock, buffer, expected_data_len, 0);

        if (read_bytes == 0) {
            break;
        } else if (read_bytes < 0) {
            perror("Error communicating with the server");
        }
        else {
            // Print to output file
            ostream << buffer << std::endl;
        }
    }

    // Inform the server the session is finished, and close the socket
    send(sock, "END", 4, 0);
    close(sock);

    return 0;
}
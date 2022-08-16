#include <iostream>
#ifdef WIN32
#include <windows.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <memory>

int main(int argc, char* argv[]) {
//    if (argc < 2) {
//        std::cout << "Usage: ./Client [UNCLASSIFIED-DATA-PATH] [OUTPUT-PATH]" << std::endl;
//        return 0;
//    }

    // Server constants
    const char* ip_address = "127.0.0.1";
    const int port_no = 5555;

    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("Error creating socket");
    }

    // Connect to the server
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);

    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("Error connecting to server");
    }

    // Send the unclassified data to the server
    std::string line, fileContent;
    std::ifstream inFile(/**argv[1]**/ "../io/Unclassified.csv");

    while (std::getline(inFile, line)) {
        fileContent += line + '\n';

        if (fileContent.size() > 512) {
            std::cout << "File Size too big, 512 is the character limit" << std::endl;
            close(sock);
            return -1;
        }
    }

    inFile.close();

    int sent_bytes = send(sock, fileContent.c_str(), fileContent.size(), 0);

    if (sent_bytes < 0) {
        perror("Error communicating with the server");
    }

    // Receive the classifications from the server
    char buffer[512] = {0};
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(sock, buffer, expected_data_len, 0);

    if (read_bytes < 0) {
        perror("Error communicating with the server");
    }

    // Write the classifications to the desired path
    std::ofstream ostream(/**argv[2]**/"../io/out");
    ostream << buffer;

    close(sock);
    return 0;
}
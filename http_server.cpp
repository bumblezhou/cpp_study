#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

constexpr int BUFFER_SIZE = 1024;

// Function to read a file and return its content as a string
std::string readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        return "";
    }

    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}

// Function to get MIME type based on file extension
std::string getMimeType(const std::string& filename) {
    static const std::unordered_map<std::string, std::string> mimeTypes = {
        {".html", "text/html"},
        {".htm", "text/html"},
        {".css", "text/css"},
        {".js", "application/javascript"},
        {".jpg", "image/jpeg"},
        {".jpeg", "image/jpeg"},
        {".png", "image/png"},
        {".gif", "image/gif"},
        {".txt", "text/plain"},
    };

    auto pos = filename.find_last_of('.');
    if (pos != std::string::npos) {
        std::string extension = filename.substr(pos);
        auto it = mimeTypes.find(extension);
        if (it != mimeTypes.end()) {
            return it->second;
        }
    }
    return "application/octet-stream"; // Default MIME type
}

// Function to handle HTTP requests
void handleRequest(int clientSocket, const std::string& rootDir) {
    char buffer[BUFFER_SIZE];
    int bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (bytesRead <= 0) {
        return;
    }
    buffer[bytesRead] = '\0';

    // Parse HTTP request (assuming a simple GET request)
    // iss content: GET /static/test.html HTTP/1.1
    std::istringstream iss(buffer);
    
    std::string method, path, version;
    iss >> method >> path >> version;

    std::cout << "================================" << std::endl;
    std::cout << "method: " << method << std::endl;
    std::cout << "path: " << path << std::endl;
    std::cout << "version: " << version << std::endl;
    std::cout << "================================" << std::endl;

    // Check if method is GET
    if (method != "GET") {
        std::string response = "HTTP/1.1 405 Method Not Allowed\r\n\r\n";
        send(clientSocket, response.c_str(), response.size(), 0);
        return;
    }

    // Construct full path to the requested file
    std::string fullPath = rootDir + path;

    // Read the file content
    std::string fileContent = readFile(fullPath);

    // Construct HTTP response
    std::ostringstream response;
    if (fileContent.empty()) {
        response << "HTTP/1.1 404 Not Found\r\n\r\n";
    } else {
        response << "HTTP/1.1 200 OK\r\n";
        response << "Content-Length: " << fileContent.size() << "\r\n";
        response << "Content-Type: " << getMimeType(fullPath) << "\r\n\r\n";
        response << fileContent;
    }

    // Send the response
    send(clientSocket, response.str().c_str(), response.str().size(), 0);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <port> <root_dir>\n";
        return 1;
    }

    int port = std::atoi(argv[1]);
    std::string rootDir = argv[2];

    // Create socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket\n";
        return 1;
    }

    // Bind socket
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error binding socket\n";
        close(serverSocket);
        return 1;
    }

    // Listen for connections
    if (listen(serverSocket, 10) == -1) {
        std::cerr << "Error listening on socket\n";
        close(serverSocket);
        return 1;
    }

    std::cout << "Server listening on port " << port << "...\n";

    // Accept incoming connections and handle requests
    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientAddrSize = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket == -1) {
            std::cerr << "Error accepting connection\n";
            continue;
        }

        // Handle request in a separate thread
        handleRequest(clientSocket, rootDir);

        // Close client socket
        close(clientSocket);
    }

    // Close server socket
    close(serverSocket);

    return 0;
}

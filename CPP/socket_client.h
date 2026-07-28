#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include <string>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#endif

class SocketClient {
public:
    SocketClient();
    ~SocketClient();

    SocketClient(const SocketClient&) = delete;
    SocketClient& operator=(const SocketClient&) = delete;

    bool connect(const std::string& host, int port);
    bool send(const std::string& data);
    std::string recv(size_t buffer_size = 4096);
    void close();
    bool is_connected() const;

private:
#ifdef _WIN32
    SOCKET sock_;
    WSADATA wsa_;
#else
    int sock_;
#endif
    bool connected_;
    void cleanup();
};

#endif

#include "socket_client.h"
#include <cstring>
#include <stdexcept>

SocketClient::SocketClient() : sock_(0), connected_(false) {
#ifdef _WIN32
    if (WSAStartup(MAKEWORD(2, 2), &wsa_) != 0)
        throw std::runtime_error("WSAStartup failed");
#endif
}

SocketClient::~SocketClient() {
    close();
#ifdef _WIN32
    WSACleanup();
#endif
}

bool SocketClient::connect(const std::string& host, int port) {
    struct addrinfo hints{}, *res;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    std::string port_str = std::to_string(port);
    if (getaddrinfo(host.c_str(), port_str.c_str(), &hints, &res) != 0)
        return false;

    sock_ = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
#ifdef _WIN32
    if (sock_ == INVALID_SOCKET) { freeaddrinfo(res); return false; }
#else
    if (sock_ < 0) { freeaddrinfo(res); return false; }
#endif

    if (::connect(sock_, res->ai_addr, static_cast<int>(res->ai_addrlen)) < 0) {
        freeaddrinfo(res);
        close();
        return false;
    }
    freeaddrinfo(res);
    connected_ = true;
    return true;
}

bool SocketClient::send(const std::string& data) {
    if (!connected_) return false;
#ifdef _WIN32
    return ::send(sock_, data.c_str(), static_cast<int>(data.size()), 0) != SOCKET_ERROR;
#else
    return ::send(sock_, data.c_str(), data.size(), 0) >= 0;
#endif
}

std::string SocketClient::recv(size_t buffer_size) {
    if (!connected_) return {};
    std::string buf(buffer_size, '\0');
#ifdef _WIN32
    int n = ::recv(sock_, &buf[0], static_cast<int>(buffer_size), 0);
    if (n <= 0) return {};
#else
    ssize_t n = ::recv(sock_, &buf[0], buffer_size, 0);
    if (n <= 0) return {};
#endif
    buf.resize(static_cast<size_t>(n));
    return buf;
}

void SocketClient::close() {
    if (connected_) {
#ifdef _WIN32
        closesocket(sock_);
#else
        ::close(sock_);
#endif
        connected_ = false;
    }
}

bool SocketClient::is_connected() const { return connected_; }

void SocketClient::cleanup() {
    close();
#ifdef _WIN32
    WSACleanup();
#endif
}

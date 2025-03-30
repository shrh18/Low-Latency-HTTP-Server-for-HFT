#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <openssl/ssl.h>
#include <atomic>

class Connection {
public:
    Connection(int fd, SSL* ssl);
    ~Connection();

    bool process_request();
    void close();

    int get_fd() const { return fd_; }
    bool is_active() const { return active_; }

private:
    int fd_{-1};  // File descriptor for the connection
    SSL* ssl_{nullptr};  // SSL object for TLS operations
    std::atomic<bool> active_{false};  // Connection status

    static constexpr size_t BUFFER_SIZE = 4096;  // Size of the buffer for reading/writing data
    alignas(64) char buffer_[BUFFER_SIZE];  // Buffer for incoming/outgoing data
    alignas(64) char write_buffer_[BUFFER_SIZE];  // Buffer for outgoing data

    bool read_request();  // Read request data from the connection
    bool write_response();  // Write response data to the connection
};
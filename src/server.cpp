#pragma once

#include <atomic>
#include <memory>
#include <vector>
#include <thread>
#include <unordered_map>
#include "connection.hpp"

class HFT_Server {
public:
    HFT_Server(int port, int thread_count = std::thread::hardware_concurrency());
    ~HFT_Server();

    void start();
    void stop();
    bool is_running() const { return running_; };

private:
    void worker_thread(int thread_id);
    void accept_connections();
    void handle_connection(Connection& conn);

    int port_;
    int listen_fd_;
    std::atomic<bool> running_{false};
    std::vector<std::thread> workers_;

    std::shared_ptr<TLS_Engine> tls_engine_;    // TLS context would be here
    std::unordered_map<int, std::unique_ptr<Connection>> connections_;  // Map of active connections, connection pools
};
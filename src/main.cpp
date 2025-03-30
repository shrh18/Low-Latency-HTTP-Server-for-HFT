#include "server.hpp"
#include "tls_engine.hpp"
#include "fault_tolerant.hpp"
#include <iostream>
#include <csignal>

std::atomic<bool> shutdown_requested{false};

void signal_handler(int signal){
    shutdown_requested.store(true);
}

int main(){
    std::signal(SIGINT, signal_handler);  // Register signal handler for graceful shutdown
    std::signal(SIGTERM, signal_handler);  // Register signal handler for graceful shutdown

    try {
        auto tls_engine = std::make_shared<TLS_Engine>();
        if (!tls->init("server.crt", "server.key")) {
            std::cerr << "Failed to initialize TLS engine." << std::endl;
            return 1;
        }
        tls_engine->configure_for_low_latency();  // Optional: configure for low latency

        HFT_Server server(8443, 4);
        server.start();

        while (!shutdown_requested.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Main thread sleeps until shutdown is requested
        }

        server.stop();  // Stop the server gracefully
    } catch (const std::exception& e) {
        std::cerr << "Fatal Exception: " << e.what() << << "\n";
        return 1;
    } 

    return 0;
}
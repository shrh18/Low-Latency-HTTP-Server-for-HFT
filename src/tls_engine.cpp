#pragma once

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <memory>

class TLS_Engine {
public:
    TLS_Engine();
    ~TLS_Engine();

    bool init(const char* cert_file, const char* key_path);
    SSl_CTX* get_context() const { return ctx_; }

    void configure_for_low_latency();

private:
    SSL_CTX* ctx_{nullptr};  // SSL context for TLS operations
    bool setup_seesion_tickets();  // Enable session tickets for session resumption
    bool setup_early_data();  // Enable early data support for 0-RTT
};
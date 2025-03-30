#pragma once

#include <vector>
#include <functional>
#include <mutex>

class Fault_Tolerance_Manager {
public:
    enum class FaultType{
        NetworkError,
        TLSHandshakeFailure,
        RequestTimeout,
        SystemResourceExhaustion,
    };

    void register_handler(FaultType type, std::function<void()> handler);
    void trigger_recovery(FaultType type);

    // Heartbeat monitoring
    void start_heartbeat_monitor();
    void stop_heartbeat_monitor();

private:
    std::unordered_map<FaultType, std::vector<std::function<void()>>> handlers_;
    std::mutex handlers_mutex_;  // Mutex to protect access to the handlers map
    std::atomic<bool> monitoring_{false};

    void initiate_failover();  // Initiate failover process
};
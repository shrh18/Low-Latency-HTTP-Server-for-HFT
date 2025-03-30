cmake_minimum_required(VERSION 3.15)
project(HFT_HTTPS_Server VERSION 1.0.0 DESCRIPTION "High Frequency Trading HTTPS Server")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
    -03
    -march=native
    mtune=native
    -flto
    -fno-exceptions
    -fno-rtti
)

find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

add_executable(hft-server
    src/main.cpp
    src/sever.cpp
    src/connection.cpp
    src/tls_engine.cpp
    src/request_handler.cpp
    src/fault_tolerance.cpp
)

target_include_directories(hft-server PRIVATE include)
target_link_libraries(hft-server PRIVATE
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
)
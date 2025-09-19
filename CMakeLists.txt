cmake_minimum_required(VERSION 3.29.6)
project(EncryptedMessenger VERSION 1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE SRC_FILES
        ${CMAKE_SOURCE_DIR}/main.cpp
        ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(app ${SRC_FILES})

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/include)

if(WIN32)
    set(OPENSSL_ROOT_DIR "C:/msys64/mingw64")
elseif(APPLE)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl@3")  # ou /usr/local
endif()
set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
set(OPENSSL_CRYPTO_LIBRARY "${OPENSSL_ROOT_DIR}/lib/libcrypto.a")
set(OPENSSL_SSL_LIBRARY "${OPENSSL_ROOT_DIR}/lib/libssl.a")

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
link_directories(${OPENSSL_LIBRARIES})
target_link_libraries(app PRIVATE OpenSSL::Crypto)

add_compile_definitions(TOKEN_DIR="${CMAKE_SOURCE_DIR}/token/")
add_compile_definitions(TEST_PEM_PATH="${CMAKE_SOURCE_DIR}/token/user1.pem")
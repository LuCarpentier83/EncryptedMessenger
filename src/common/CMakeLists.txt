add_library(common 
    crypto/Crypto.cpp
    net/Socket.cpp
)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

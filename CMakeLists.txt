cmake_minimum_required(VERSION 3.29.6)
project(EncryptedMessenger VERSION 1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SRC_FILES
        ${CMAKE_SOURCE_DIR}/main.cpp
        ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(app ${SRC_FILES})

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/include)
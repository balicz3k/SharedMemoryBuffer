cmake_minimum_required(VERSION 3.20)

project(SharedMemBuffer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(smb INTERFACE)
target_include_directories(smb INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(UNIX AND NOT APPLE)
    target_link_libraries(smb INTERFACE rt pthread)
endif()

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE smb)

enable_testing()
add_subdirectory(tests)
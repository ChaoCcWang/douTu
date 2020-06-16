cmake_minimum_required(VERSION 3.12)
project(douTu)
set(CMAKE_CXX_STANDARD 14)

if(UNIX)
    add_definitions("-Wall -g")
    set(QT_HOME /usr/local/opt/qt/)
    set(CMAKE_CXX_FLAGS -fPIC)
    include_directories(/usr/local/opt/openssl/include)
    include_directories(/usr/local/include)
    link_directories(/usr/local/opt/openssl/lib)
    link_directories(/usr/local/lib)
endif ()

include_directories(c-gumbo)

add_subdirectory(gumbo)
add_subdirectory(douTu)

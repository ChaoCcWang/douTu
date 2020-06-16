project(douTu)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets)

set(SOURCE_FILE
        ${CMAKE_SOURCE_DIR}/http/HttpRequest.h
        ${CMAKE_SOURCE_DIR}/http/QtHttpRequest.cpp
        ${CMAKE_SOURCE_DIR}/http/QtHttpRequest.h
        douTu.qrc
        main.cpp
        DouTu.h
        DouTu.cpp
        RequestThread.cpp
        RequestThread.h
        CellWgt.cpp CellWgt.h
        HttpHelper.cpp HttpHelper.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILE})

target_link_libraries(${PROJECT_NAME}
        Qt5::Widgets
        gumbo
        curl)


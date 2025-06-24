cmake_minimum_required(VERSION 3.16)
project(QTLudo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(HEADERS
    ./src/Menu.h
    ./src/MainWindow.h
)

set(SOURCES
    ./src/main.cpp
    ./src/Menu.cpp
    ./src/MainWindow.cpp
)

set(UI
    ./src/Menu.ui
)


find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UI})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)

cmake_minimum_required(VERSION 3.16)
project(QTLudo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB CPP "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB HPP "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB UI "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui")
set(SRC
    ${CPP}
    ${HPP}
    ${UI}
)
file(GLOB TEST "${CMAKE_CURRENT_SOURCE_DIR}/src/*_test.cpp")

message("Test ${TEST}")

list(REMOVE_ITEM SRC ${TEST})

message("SRC ${SRC}")

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)

add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::OpenGLWidgets Qt6::Widgets Qt6::Core Qt6::Gui)
target_sources(${PROJECT_NAME} PRIVATE ${SRC})

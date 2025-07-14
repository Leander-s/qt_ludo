cmake_minimum_required(VERSION 3.16)
project(QTLudo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB UI "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui")

# message("Using these sources ${SOURCES}")


find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UI})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::OpenGLWidgets Qt6::Widgets Qt6::Core Qt6::Gui)

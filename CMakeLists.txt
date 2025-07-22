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
file(GLOB TEST_UTIL "${CMAKE_CURRENT_SOURCE_DIR}/test_util/*.cpp")
file(GLOB TEST "${CMAKE_CURRENT_SOURCE_DIR}/src/*_test.cpp")

set(SRC
    ${CPP}
    ${UI}
)

set(LIBS
    Qt6::OpenGLWidgets 
    Qt6::Widgets 
    Qt6::Core 
    Qt6::Gui
)

list(REMOVE_ITEM SRC ${TEST})
list(REMOVE_ITEM SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)

add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})
target_sources(${PROJECT_NAME} PRIVATE ${SRC} ./src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/"
    "${CMAKE_CURRENT_SOURCE_DIR}/test_util/"
)

foreach(TEST_FILE IN LISTS TEST)
    get_filename_component(TEST_NAME "${TEST_FILE}" NAME_WE)

    add_executable(
        ${TEST_NAME}
        ${TEST_FILE}
        ${SRC}
        ${TEST_UTIL}
    )

    target_link_libraries(${TEST_NAME} PRIVATE ${LIBS})
    target_include_directories(${TEST_NAME} PRIVATE 
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"
        "${CMAKE_CURRENT_SOURCE_DIR}/test_util/"
    )
endforeach()

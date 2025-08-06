cmake_minimum_required(VERSION 3.16)
project(QTLudo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(QT_LIBS
    Qt6::OpenGLWidgets 
    Qt6::Widgets 
    Qt6::Core 
    Qt6::Gui
)
find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)

file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB HPP "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB UI "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui")
file(GLOB TEST_UTIL "${CMAKE_CURRENT_SOURCE_DIR}/test_util/*.cpp")
file(GLOB TEST_UTIL_HPP "${CMAKE_CURRENT_SOURCE_DIR}/test_util/*.h")
file(GLOB TEST "${CMAKE_CURRENT_SOURCE_DIR}/src/*_test.cpp")


list(REMOVE_ITEM SRC ${TEST})
list(REMOVE_ITEM SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_library(core STATIC ${SRC})
target_include_directories(core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
target_link_libraries(core PUBLIC ${QT_LIBS})

add_library(test_util STATIC ${TEST_UTIL})
target_include_directories(test_util PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/test_util/")
target_link_libraries(test_util PUBLIC ${QT_LIBS})

add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE core)
target_sources(${PROJECT_NAME} PRIVATE src/main.cpp ${HPP})

foreach(TEST_FILE IN LISTS TEST)
    get_filename_component(TEST_NAME "${TEST_FILE}" NAME_WE)

    add_executable(
        ${TEST_NAME}
    )

    target_link_libraries(${TEST_NAME} PRIVATE core test_util)
    target_sources(${TEST_NAME} PRIVATE ${TEST_FILE} ${TEST_UTIL_HPP})
endforeach()

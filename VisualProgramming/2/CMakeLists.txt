cmake_minimum_required(VERSION 3.5)

project(Laba2 LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

### CORE
add_library(Laba2Core
    src/Core/CustomUILoader.cpp
    src/Core/CustomUILoader.variant.cpp
    src/Core/CustomUILoader.layout.cpp
    src/Core/CustomUILoader.widget.cpp)

target_include_directories(Laba2Core PUBLIC src/)
target_compile_features(Laba2Core PUBLIC cxx_std_17)
target_link_libraries(Laba2Core PUBLIC Qt5::Widgets)
target_link_libraries(Laba2Core PUBLIC Qt5::Core)

add_executable(Laba2
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        src/windowFrom1Laba.ui
    )
target_link_libraries(Laba2 PUBLIC Laba2Core)

FILE(COPY src/windowFrom1Laba.ui DESTINATION ${CMAKE_CURRENT_BINARY_DIR})





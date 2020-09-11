cmake_minimum_required(VERSION 3.5)

project(Pochta_Laba1 LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)


add_executable(Pochta_Laba1
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
)

target_include_directories(Pochta_Laba1 PRIVATE src/)
target_compile_features(Pochta_Laba1 PRIVATE cxx_std_17)

target_link_libraries(Pochta_Laba1 PRIVATE Qt5::Widgets)

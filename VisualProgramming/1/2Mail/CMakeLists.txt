cmake_minimum_required(VERSION 3.5)

project(Mail_Laba2 LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)


add_executable(Mail_Laba2
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
)

target_include_directories(Mail_Laba2 PRIVATE src/)
target_compile_features(Mail_Laba2 PRIVATE cxx_std_17)

target_link_libraries(Mail_Laba2 PRIVATE Qt5::Widgets)

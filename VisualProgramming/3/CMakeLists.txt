cmake_minimum_required(VERSION 3.5)

project(FoodTrack LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(FoodTrack
        src/main.cpp
        src/QueueModel.cpp
        src/MainWindow.cpp
        src/MainWindow.ui)

target_include_directories(FoodTrack PRIVATE src/)
target_compile_features(FoodTrack PRIVATE cxx_std_20)
target_link_libraries(FoodTrack PRIVATE Qt5::Widgets)
target_link_libraries(FoodTrack PRIVATE Qt5::Core)






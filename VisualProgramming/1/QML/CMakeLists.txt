cmake_minimum_required(VERSION 3.5)

project(3QML LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

add_executable(3QML
    src/main.cpp
    src/qml.qrc
)

target_include_directories(3QML PRIVATE src/)
target_compile_features(3QML PRIVATE cxx_std_17)


target_compile_definitions(3QML
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(3QML
  PRIVATE Qt5::Core Qt5::Quick)

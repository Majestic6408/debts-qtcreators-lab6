cmake_minimum_required(VERSION 3.16)
project(lab6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(lab6
    main.cpp
    MainWindow.cpp
    MainWindow.h
    Bag.cpp
    Bag.h

)

target_link_libraries(lab6 Qt6::Widgets)

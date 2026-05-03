cmake_minimum_required(VERSION 4.1)
project(ElectrostaticSystem)

set(CMAKE_CXX_STANDARD 14)

add_executable(ElectrostaticSystem
        TAD/ElectrostaticSystem.h
        TAD/ElectrostaticSystem.cpp
        ui/UI.cpp
        ui/UI.h
        main.cpp)

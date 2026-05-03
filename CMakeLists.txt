cmake_minimum_required(VERSION 3.31)
project(ElectrostaticSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(ElectrostaticSystem main.cpp
        ui/UI.cpp
        ui/UI.h
        TAD/ElectrostaticSystem.cpp
        TAD/ElectrostaticSystem.h
)

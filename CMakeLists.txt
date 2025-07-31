cmake_minimum_required(VERSION 3.30)
project(GameMaxxing)

set(CMAKE_CXX_STANDARD 14)

include_directories(Algorithms)

add_executable(GameMaxxing
    Algorithms/Game.cpp
    Algorithms/Game.h
    Algorithms/Heap.cpp
    Algorithms/Heap.h
    main.cpp)

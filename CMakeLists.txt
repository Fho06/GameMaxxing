cmake_minimum_required(VERSION 3.16)
project(GameMaxxing)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DSFML_STATIC)

include_directories(
    src
    SFML/include
)

link_directories(
    SFML/lib
    )

add_executable(
        GameMaxxing
        src/DatasetHLTB.cpp
        src/DatasetHLTB.h
        src/main.cpp
        "SFMLObjects/Button.cpp"
        "SFMLObjects/Button.h"
        "SFMLObjects/Textbox.cpp"
        "SFMLObjects/Textbox.h"
        "SFMLObjects/GameCard.cpp"
        "SFMLObjects/GameCard.h"
        src/RedBlackTree.cpp
        src/RedBlackTree.h
        src/Heap.cpp
        src/Heap.h
        src/game.cpp
        src/game.h
        )

target_link_libraries(
    GameMaxxing
    sfml-graphics-s
    sfml-window-s
    sfml-system-s
    freetype
    opengl32
    winmm
    gdi32
    user32
)
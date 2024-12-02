cmake_minimum_required(VERSION 3.28.1)
project(Laying_Grass)

set(CMAKE_CXX_STANDARD 20)

set(RAYLIB_VERSION 4.2.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

add_executable(Laying_Grass src/main.cpp
        src/Player.cpp
        header/Player.h
        src/Board.cpp
        header/Board.h
        src/Case.cpp
        header/Case.h
        src/BoardDisplay.cpp
        header/BoardDisplay.h
        src/Game.cpp
        header/Game.h
        src/Tiles.cpp
        header/Tiles.h
        src/DisplayMenu.cpp
        header/DisplayMenu.h
        src/displayWin.cpp
        header/displayWin.h
        src/Bonus.cpp
        header/Bonus.h
        src/Tiles.cpp
        src/Player.cpp
)

target_link_libraries(Laying_Grass raylib ws2_32)
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

add_executable(Laying_Grass FILES/main.cpp
        FILES/Player.cpp
        FILES/Player.h
        FILES/Board.cpp
        FILES/Board.h
        FILES/Case.cpp
        FILES/Case.h
        FILES/BoardDisplay.cpp
        FILES/BoardDisplay.h
        FILES/Game.cpp
        FILES/Game.h
        FILES/Tiles.cpp
        FILES/Tiles.h
        FILES/DisplayMenu.cpp
        FILES/DisplayMenu.h
        FILES/displayWin.cpp
        FILES/displayWin.h
        FILES/Bonus.cpp
        FILES/Bonus.h
)

target_link_libraries(Laying_Grass raylib ws2_32)
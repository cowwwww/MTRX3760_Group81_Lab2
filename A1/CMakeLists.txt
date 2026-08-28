cmake_minimum_required(VERSION 3.10)

project(wall_follower)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Location of raylib installed by Homebrew.
set(raylib_DIR "/opt/homebrew/Cellar/raylib/6.0/lib/cmake/raylib")

find_package(raylib CONFIG REQUIRED)

add_executable(wall_follower
    main.cpp
    CSimulation.cpp
    CWallFollower.cpp
    CRobot.cpp
    CRangeSensor.cpp
    CWallMap.cpp
    CLoopReader.cpp
    CRender.cpp
)

target_link_libraries(wall_follower PRIVATE raylib)
cmake_minimum_required(VERSION 3.10)

project(wall_follower)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic")

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

configure_file(SimpleWalls.map SimpleWalls.map COPYONLY)

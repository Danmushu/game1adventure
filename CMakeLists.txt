cmake_minimum_required(VERSION 3.25)
project(Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static")


include_directories(.)


add_executable(Game

        src/Fight.h
        src/Location.h
        src/Main.cpp
        src/Map.h
        src/Monster.h
        src/Backpack.h
        src/Item.h
        src/Interface.h

        src/GameController.h)
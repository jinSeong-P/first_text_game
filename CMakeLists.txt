cmake_minimum_required(VERSION 3.31)
project(Textgame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Textgame main.cpp Space.cpp Action.cpp World.cpp)


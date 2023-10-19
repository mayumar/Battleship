cmake_minimum_required(VERSION 3.0)
project(p2redes)

add_executable(jueguito src/main.cpp src/classes/ship/Ship.cpp src/classes/board/Board.cpp src/aux/aux.cpp src/server/server.cpp)
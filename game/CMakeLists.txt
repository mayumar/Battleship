cmake_minimum_required(VERSION 3.0)
project(p2redes)

add_executable(jueguito src/main.cpp src/classes/game/Game.cpp src/classes/ship/Ship.cpp src/classes/board/Board.cpp src/classes/player/Player.cpp src/aux/aux.cpp src/server/server.cpp src/auth/auth.cpp src/commands/commands.cpp)
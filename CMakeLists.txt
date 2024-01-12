CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)
PROJECT(ProvaFinaleMonopolyBarbatoCasucciPinton LANGUAGES CXX)

add_compile_options(-O2)

include_directories(include)
add_library(BoardLib STATIC "./include/Position.h" "./include/Board.h" "./include/Tile.h" "./src/Board.cpp" "./src/Tile.cpp" "./src/Position.cpp")
add_library(PlayerLib STATIC "./include/Player.h" "./include/Bot.h" "./include/Human.h" "./src/Player.cpp" "./src/Bot.cpp" "./src/Human.cpp" )
add_library(MonoPolyGameLib STATIC "./include/MonopolyGame.h" "./include/Logger.h" "./include/EventType.h" "./src/MonopolyGame.cpp" "./src/Logger.cpp" )
add_executable(monopoly "./src/main.cpp")
target_link_libraries( BoardLib PlayerLib MonoPolyGameLib)
target_link_libraries( PlayerLib BoardLib  MonoPolyGameLib)
target_link_libraries( MonoPolyGameLib BoardLib PlayerLib )
target_link_libraries(monopoly BoardLib PlayerLib MonoPolyGameLib)

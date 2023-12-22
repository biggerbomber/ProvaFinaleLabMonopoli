CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)
PROJECT(ProvaFinaleMonopolyBarbatoCasucciPinton LANGUAGES CXX)
ADD_EXECUTABLE(monopolyGameTester
	"./src/Board.cpp"
	"./src/Bot.cpp"
	"./src/Human.cpp"
	"./src/main.cpp"
	"./src/MonopolyGame.cpp"
   	"./src/Player.cpp"
   	"./src/Position.cpp"
    	"./src/Tile.cpp"
	"./include/Board.h"
	"./include/Bot.h"
    	"./include/Human.h"
	"./include/MonopolyGame.h"
   	"./include/Player.h"
	"./include/Position.h"
	"./include/Tile.h"
)
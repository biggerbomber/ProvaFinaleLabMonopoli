#include "../include/MonopolyGame.h"
#include "../include/Board.h"
#include "../include/Position.h"
#include <iostream>

int main(int argc , char** argv){
    /*MonopolyGame m(MonopolyGame::PlayerType::HUMAN);
    m.run();*/

    for(int i=0;i<Board::BOARD_SIZE;i++){
        std::cout<<Position(i)<<std::endl;
    }

}
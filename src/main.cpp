#include "../include/MonopolyGame.h"
#include "../include/Board.h"
#include "../include/Position.h"
#include "../include/Tile.h"
#include <iostream>

int main(int argc , char** argv){
    MonopolyGame m(MonopolyGame::PlayerType::BOT);


    for(int i=0;i<Board::BOARD_SIZE;i++){
        std::cout<<Position(i)<<std::endl;
    }

    Tile t(Tile::ANGOLARE);
    std::cout << t;

    Board b();
    t.set_tile_type(Tile::ECONOMICA);
    t.set_build_type(Tile::ALBERGO);
    //t.set_proprietario(3);
    std::cout << t;
    t.set_build_type(Tile::CASA);
    t.set_tile_type(Tile::LUSSO);
    std::cout << t;


    m.log(Logger::PASSAGGIO_VIA,2);
    m.log(Logger::PAGAMENTO_PERNOTTAMENTO,4,Position(7),1,30);
    m.log(Logger::TIRO_DADI, 2,12);
    m.log(Logger::ELIMINAZIONE, 2);
    m.log(Logger::COSTRUZIONE_ALBERGO, 2,Position(10));
    m.log(Logger::ACQUISTO_TERRENO, 2,Position(20));


}